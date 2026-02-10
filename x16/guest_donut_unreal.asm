;
; Unreal-mode spinning torus ("full donut") sample:
; - Host-provided flat 4 GiB data segments via module_unreal_impl.inc
; - x87 parametric torus + 3D rotation matrix
; - Perspective projection + floating-point Z buffer
; - Direct 32-bit LFB writes through GS:EDI + MMIO present
;

include 'module_unreal_impl.inc'
include 'module_flags.inc'

Set_Module_Flags_V0 0, MODULE_CAP_MMIO_FRAMEBUFFER or MODULE_CAP_UNREAL_SEGMENTS, 0

use16
org 0x2000

WIDTH      = LFB_WIDTH
HEIGHT     = LFB_HEIGHT
PIXELS     = WIDTH * HEIGHT
CENTER_X   = WIDTH / 2
CENTER_Y   = HEIGHT / 2
ZBUF_BYTES = PIXELS * 4

start:

    fninit
.frame:
    ; Clear LFB (BGRA = 0x00000000).
    mov edi, LFB_BASE
    mov ecx, PIXELS
    xor eax, eax
    db 67h ; use EDI
    rep stosd

    ; Clear Z buffer to 0.0 (we store inverse-Z; larger is closer).
    mov edi, zbuffer
    mov ecx, PIXELS
    db 67h ; use EDI
    rep stosd

    ; Animate rotation.
    fld dword [angle_x]
    fadd dword [speed_x]
    fstp dword [angle_x]

    fld dword [angle_y]
    fadd dword [speed_y]
    fstp dword [angle_y]

    call build_rotation_matrix

    mov word [v_step], 0

.v_loop:
    ; v in [0, 2*pi)
    fild word [v_step]
    fmul dword [two_pi]
    fidiv word [v_segments]
    fsincos
    fstp dword [cos_v]
    fstp dword [sin_v]

    ; ring_radius = major + minor*cos(v)
    fld dword [minor_radius]
    fmul dword [cos_v]
    fadd dword [major_radius]
    fstp dword [ring_radius]

    mov word [u_step], 0

.u_loop:
    ; u in [0, 2*pi)
    fild word [u_step]
    fmul dword [two_pi]
    fidiv word [u_segments]
    fsincos
    fstp dword [cos_u]
    fstp dword [sin_u]

    ; Local torus point:
    ; px = (R + r*cos(v)) * cos(u)
    ; py = (R + r*cos(v)) * sin(u)
    ; pz = r * sin(v)
    fld dword [ring_radius]
    fmul dword [cos_u]
    fstp dword [px]

    fld dword [ring_radius]
    fmul dword [sin_u]
    fstp dword [py]

    fld dword [minor_radius]
    fmul dword [sin_v]
    fstp dword [pz]

    ; Local normal on torus surface:
    ; nx = cos(u)*cos(v), ny = sin(u)*cos(v), nz = sin(v)
    fld dword [cos_u]
    fmul dword [cos_v]
    fstp dword [nx]

    fld dword [sin_u]
    fmul dword [cos_v]
    fstp dword [ny]

    fld dword [sin_v]
    fstp dword [nz]

    call rotate_point
    call rotate_normal

    ; Camera offset in +Z.
    fld dword [tz]
    fadd dword [camera_z]
    fstp dword [tz]

    ; Near-plane clip.
    fld dword [tz]
    fcomp dword [near_plane]
    fstsw ax
    sahf
    jbe .skip_point

    ; invz = 1 / z
    fld1
    fdiv dword [tz]
    fstp dword [invz]

    ; screen_x = tx * focal * invz + CENTER_X
    fld dword [tx]
    fmul dword [focal_length]
    fmul dword [invz]
    fiadd word [center_x]
    fistp dword [screen_x]

    ; screen_y = -ty * focal * invz + CENTER_Y
    fld dword [ty]
    fmul dword [focal_length]
    fmul dword [invz]
    fchs
    fiadd word [center_y]
    fistp dword [screen_y]

    ; Bounds.
    mov eax, [screen_x]
    cmp eax, 0
    jl .skip_point
    cmp eax, WIDTH
    jge .skip_point

    mov ebx, [screen_y]
    cmp ebx, 0
    jl .skip_point
    cmp ebx, HEIGHT
    jge .skip_point

    ; pixel_offset = ((y * WIDTH) + x) * 4
    imul ebx, WIDTH
    add ebx, eax
    shl ebx, 2
    mov [pixel_offset], ebx

    ; Z test: closer if invz is larger.
    mov edi, zbuffer
    add edi, ebx
    fld dword [invz]
    fcomp dword [edi]
    fstsw ax
    sahf
    jbe .skip_point

    ; Store new invz.
    fld dword [invz]
    fstp dword [edi]

    ; Directional lighting:
    ; dot = max(0, dot(rotated_normal, light_dir))
    fld dword [tnx]
    fmul dword [light_x]
    fld dword [tny]
    fmul dword [light_y]
    faddp st1, st0
    fld dword [tnz]
    fmul dword [light_z]
    faddp st1, st0

    ftst
    fstsw ax
    sahf
    jae .dot_non_negative
    fstp st0
    fldz

.dot_non_negative:
    ; shade = ambient + diffuse_strength * dot
    fmul dword [diffuse_strength]
    fadd dword [ambient]

    ; Clamp shade <= 1.0
    fld1
    fcom st1
    fstsw ax
    sahf
    jae .shade_ok
    fstp st0
    fstp st0
    fld1
    jmp .shade_ready

.shade_ok:
    fstp st0

.shade_ready:
    ; intensity = clamp(int(shade * 255), 0..255)
    fmul dword [f_255]
    fistp dword [intensity]

    mov eax, [intensity]
    cmp eax, 0
    jge .int_hi
    xor eax, eax
.int_hi:
    cmp eax, 255
    jle .int_ok
    mov eax, 255
.int_ok:
    ; Cyan/teal ramp:
    ; B = i
    ; G = min(i + i/2, 255)
    ; R = i/4
    mov edx, eax                    ; B
    mov ecx, eax
    shr ecx, 1
    add ecx, eax                    ; G
    cmp ecx, 255
    jle .g_ok
    mov ecx, 255
.g_ok:
    mov esi, eax
    shr esi, 2                      ; R
    shl esi, 16
    shl ecx, 8
    or esi, ecx
    or esi, edx

    mov edi, [pixel_offset]
    mov [LFB_BASE + edi], esi

.skip_point:
    inc word [u_step]
    mov ax, [u_step]
    cmp ax, [u_segments]
    jb .u_loop

    inc word [v_step]
    mov ax, [v_step]
    cmp ax, [v_segments]
    jb .v_loop

    mov byte [MMIO_BASE + REG_FB_PRESENT], 1
    jmp .frame

; matrix = Ry * Rx
build_rotation_matrix:
    fld dword [angle_x]
    fsincos
    fstp dword [cos_x]
    fstp dword [sin_x]

    fld dword [angle_y]
    fsincos
    fstp dword [cos_y]
    fstp dword [sin_y]

    fld dword [cos_y]
    fstp dword [matrix + 0]

    fld dword [sin_x]
    fmul dword [sin_y]
    fstp dword [matrix + 4]

    fld dword [cos_x]
    fmul dword [sin_y]
    fstp dword [matrix + 8]

    fldz
    fstp dword [matrix + 12]

    fld dword [cos_x]
    fstp dword [matrix + 16]

    fld dword [sin_x]
    fchs
    fstp dword [matrix + 20]

    fld dword [sin_y]
    fchs
    fstp dword [matrix + 24]

    fld dword [sin_x]
    fmul dword [cos_y]
    fstp dword [matrix + 28]

    fld dword [cos_x]
    fmul dword [cos_y]
    fstp dword [matrix + 32]
    ret

; Rotate point (px,py,pz) -> (tx,ty,tz)
rotate_point:
    fld dword [px]
    fmul dword [matrix + 0]
    fld dword [py]
    fmul dword [matrix + 12]
    faddp st1, st0
    fld dword [pz]
    fmul dword [matrix + 24]
    faddp st1, st0
    fstp dword [tx]

    fld dword [px]
    fmul dword [matrix + 4]
    fld dword [py]
    fmul dword [matrix + 16]
    faddp st1, st0
    fld dword [pz]
    fmul dword [matrix + 28]
    faddp st1, st0
    fstp dword [ty]

    fld dword [px]
    fmul dword [matrix + 8]
    fld dword [py]
    fmul dword [matrix + 20]
    faddp st1, st0
    fld dword [pz]
    fmul dword [matrix + 32]
    faddp st1, st0
    fstp dword [tz]
    ret

; Rotate normal (nx,ny,nz) -> (tnx,tny,tnz)
rotate_normal:
    fld dword [nx]
    fmul dword [matrix + 0]
    fld dword [ny]
    fmul dword [matrix + 12]
    faddp st1, st0
    fld dword [nz]
    fmul dword [matrix + 24]
    faddp st1, st0
    fstp dword [tnx]

    fld dword [nx]
    fmul dword [matrix + 4]
    fld dword [ny]
    fmul dword [matrix + 16]
    faddp st1, st0
    fld dword [nz]
    fmul dword [matrix + 28]
    faddp st1, st0
    fstp dword [tny]

    fld dword [nx]
    fmul dword [matrix + 8]
    fld dword [ny]
    fmul dword [matrix + 20]
    faddp st1, st0
    fld dword [nz]
    fmul dword [matrix + 32]
    faddp st1, st0
    fstp dword [tnz]
    ret

align 4
major_radius      dd 1.35
minor_radius      dd 0.55
focal_length      dd 190.0
camera_z          dd 3.75
near_plane        dd 0.20
angle_x           dd 0.0
angle_y           dd 0.0
speed_x           dd 0.0003
speed_y           dd 0.0005
two_pi            dd 6.283185307
ambient           dd 0.18
diffuse_strength  dd 0.82
f_255             dd 255.0
light_x           dd 0.57735026
light_y           dd 0.57735026
light_z           dd 0.57735026

u_segments        dw 96
v_segments        dw 64
center_x          dw CENTER_X
center_y          dw CENTER_Y
u_step            dw 0
v_step            dw 0

matrix            dd 9 dup (0.0)

sin_x             dd 0.0
cos_x             dd 0.0
sin_y             dd 0.0
cos_y             dd 0.0
sin_u             dd 0.0
cos_u             dd 0.0
sin_v             dd 0.0
cos_v             dd 0.0
ring_radius       dd 0.0

px                dd 0.0
py                dd 0.0
pz                dd 0.0
tx                dd 0.0
ty                dd 0.0
tz                dd 0.0
nx                dd 0.0
ny                dd 0.0
nz                dd 0.0
tnx               dd 0.0
tny               dd 0.0
tnz               dd 0.0
invz              dd 0.0

screen_x          dd 0
screen_y          dd 0
pixel_offset      dd 0
intensity         dd 0

; Keep zbuffer last so frequently accessed scalar data remains in low offsets.
zbuffer           rb ZBUF_BYTES

