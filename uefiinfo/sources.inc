!IF 0

Copyright (c) Microsoft Corporation

Module Name:

    sources.inc

Abstract:

    This file specifies the target component being built and the list of
    sources files needed to build that component.

!ENDIF

BOOTAPPNAME=uefiinfo

!include $(PROJECT_ROOT)\boot\environ\app\bootapp.inc
!include $(BASEDIR)\data\bootenv.inc
!include $(BASEDIR)\data\boot\bootlib.inc

# Compiler warning level 4
#
MSC_WARNING_LEVEL=/W4

BUILD_FOR_CORESYSTEM=1
USE_DEFAULT_WIN32_LIBS=0

BOOT_LOADER_CRITICAL=1

#
# Uncomment this define to generate .cod files
#
#USER_C_FLAGS=$(USER_C_FLAGS) /FAcs

# special compilation settings used to produce an EFI app
C_DEFINES=$(C_DEFINES) -DUNICODE
C_DEFINES=$(C_DEFINES) -D_UNICODE
C_DEFINES=$(C_DEFINES) -DWINNT
C_DEFINES=$(C_DEFINES) -DDEVL
C_DEFINES=$(C_DEFINES) -GL

INCLUDES=$(INCLUDES);\
    $(BOOT_DIR)\inc;\
    $(MINWIN_INTERNAL_PRIV_SDK_INC_PATH_L)\crypto; \
    $(PROJECT_ROOT)\boot\environ\inc; \


SOURCES=                                       \
    blmissing.c                                \
    buffer.c                                   \
    boot_options.c                             \
    file.c                                     \
    debug.c                                    \
    edk2compat.c                               \
    guids.c                                    \
    memory_map.c                               \
    network_common.c                           \
    protocols.c                                \
    safe_arithmetic.c                          \
    session.c                                  \
    testsuites.c                               \
    tsblockio.c                                \
    tsblockio.writeallblocks.c                 \
    tsblockio2.c                               \
    tsblockio2.writeallblocksasync.c           \
    tsboot.c                                   \
    tsbootmanagerpolicy.c                      \
    tscbmr.c                                   \
    tsconsoleoutput.c                          \
    tsdevicepath.c                             \
    tsdhcp4.c                                  \
    tsdhcp6.c                                  \
    tsfont.c                                   \
    tsgraphicsoutput.c                         \
    tsgraphicsoutput.rgb.c                     \
    tshash.c                                   \
    tshttp.c                                   \
    tsip4config2.c                             \
    tsip6config.c                              \
    tsloadedimage.c                            \
    tsmemory.c                                 \
    tsramdisk.c                                \
    tsreadiness.c                              \
    tsrng.c                                    \
    tsfilesystem.c                             \
    tssmbios.c                                 \
    tstcp4.c                                   \
    tstcp4.duthost.directperf.c                \
    tstcp4.duthost.directsendreceive.c         \
    tstcp6.c                                   \
    tstextinput.c                              \
    tstimestamp.c                              \
    tsudp4.c                                   \
    tsudp4.duthost.directperf.c                \
    tsudp4.duthost.directsendreceive.c         \
    tsudp6.c                                   \
    tsui.c                                     \
    tsusbfnio.c                                \
    tsusbinit.c                                \
    tsvariable.c                               \
    tswifi.c                                   \
    tswindbg.c                                 \
    uefiinfo.c                                 \
    utils.c                                    \

COMPILER_FLAGS=\
-entry:Main \
-subsystem:EFI_APPLICATION

NTTARGETFILE1=\
    $(OBJ_PATH)\$(O)\$(BOOTAPPNAME).$(TARGETEXTENSION) \

!if "$(SECONDTARGETNAME)" != ""
NTTARGETFILE2=\
    $(NTTARGETFILE2) \
    $(OBJ_PATH)\$(O)\$(SECONDTARGETNAME).$(TARGETEXTENSION) \
!endif

!if "$(BOOTARCHNAME)" != ""
NTTARGETFILE2=\
    $(NTTARGETFILE2) \
    $(OBJ_PATH)\$(O)\$(BOOTARCHNAME).$(TARGETEXTENSION) \
!endif

