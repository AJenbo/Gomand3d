cmake_minimum_required(VERSION 3.10)
project(Gomand3d LANGUAGES C CXX)

cmake_policy(SET CMP0072 NEW)

include_directories(${CMAKE_SOURCE_DIR}/INCLUDE)

option(ASAN "Enable address sanitizer" OFF)
option(UBSAN "Enable undefined behaviour sanitizer" OFF)
option(DOWNLOAD_DEPENDENCIES "Fetch SDL3 instead of finding it on the system" ON)

if (DOWNLOAD_DEPENDENCIES)
    message(STATUS "📦 Fetching SDL3...")

    include(FetchContent)
    FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG main
        EXCLUDE_FROM_ALL
    )
    FetchContent_MakeAvailable(SDL3)
else()
    find_package(SDL3 CONFIG REQUIRED)
endif()

if (ASAN)
  add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
  add_link_options(-fsanitize=address)
endif()

if (UBSAN)
  add_compile_options(-fsanitize=undefined -fno-sanitize-recover=undefined)
  add_link_options(-fsanitize=undefined)
endif()

set(SOURCES
    SOURCE/BINLOAD.C
    SOURCE/BLDGBOOM.C
    SOURCE/BOINK2.C
    SOURCE/CAMERA.C
    SOURCE/CARS.C
    SOURCE/CLUTTER.C
    SOURCE/D3CODE.C
    SOURCE/D3DAPP.C
    SOURCE/D3DCALLS.C
    SOURCE/DDCALLS.C
    SOURCE/FLY.CPP
    SOURCE/GLOBAL.C
    SOURCE/GOSYS.C
    SOURCE/ICHARS.C
    SOURCE/IMISC.C
    SOURCE/KSBLD.C
    SOURCE/LANDSCAP.C
    SOURCE/LCLIB.C
    SOURCE/LHBLDG.C
    SOURCE/LMBLDG.C
    SOURCE/LNBLDG.C
    SOURCE/LRBLDG.C
    SOURCE/LSBLDG.C
    SOURCE/LTBLDG.C
    SOURCE/LXBLDG.C
    SOURCE/MDTEX.C
    SOURCE/MISC.C
    SOURCE/MONANIM2.C
    SOURCE/MONMOVE2.C
    SOURCE/MONTHINK.C
    SOURCE/MSTRCONV.C
    SOURCE/MSTRHELP.C
    SOURCE/NETINIT2.C
    SOURCE/NETMENU.CPP
    SOURCE/NETPLAY.C
    SOURCE/PSYSTEM.C
    SOURCE/RADAR.C
    SOURCE/RL2D3D.C
    SOURCE/RMFULL.CPP
    SOURCE/RMSTATS.CPP
    SOURCE/ROBOTA~1.C
    SOURCE/ROBOTM~1.C
    SOURCE/SPRITE.C
    SOURCE/SPUDBMP.C
    SOURCE/TEKANIM.C
    SOURCE/TEKMATH.C
    SOURCE/TEXTURE.C
    SOURCE/TIMING.C
    SOURCE/TKINPUT.CPP
    SOURCE/TWIST.C
    SOURCE/WASSERT.C
    SOURCE/WAVE.C
    SOURCE/WRAPPER.CPP
    SOURCE/XAF.CPP
    SOURCE/YBJOYSTK.C
    SOURCE/YBMID.C
    SOURCE/YBMM.C
    SOURCE/YBMOUSE.C
    SOURCE/YBREG.C
    SOURCE/YBSND.C
)

add_executable(Gomand3d ${SOURCES})

target_compile_definitions(Gomand3d PRIVATE
    _WINDOWS
    _ITC_D3D_
    CDRequired
    FREEWARE
    USE320
)

target_link_libraries(Gomand3d PRIVATE SDL3::SDL3)

if (WIN32)
    target_link_libraries(Gomand3d
        d3drm ddraw dinput dsound dplayx
        user32 gdi32 winmm ole32 oleaut32 version
        comdlg32 shell32 advapi32
    )
else()
    add_subdirectory(miniwin EXCLUDE_FROM_ALL)
    target_link_libraries(Gomand3d PRIVATE miniwin)
endif()
