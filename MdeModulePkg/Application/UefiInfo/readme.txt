Software/Tools:
    1. Install ASL from https://acpica.org/downloads/binary-tools to C:\ASL\ (Do not install it to anywhere else!)
    2. Install NASM and set below NASM_PREFIX accordingly
    3. Install Python and set below PYTHON_HOME accordingly
    4. Install Visual Studio 2019
    5. Install LLVM/Clang and set below CLANG_BIN accordingly

Get all edk2 sources:
    - D:\repos>git clone https://github.com/tianocore/edk2 edk2
    - cd edk2
    - git submodule update --init --recursive

Launch build environment:
    - set PATH=D:\tools\iasl;%PATH%
    - set PYTHON_HOME=C:\Users\vineelko\AppData\Local\Programs\Python\Python311
    - set NASM_PREFIX=D:\tools\nasm\
    - set CLANG_BIN=C:\Program Files\LLVM\bin\
    - edksetup.bat VS2019
    - edit Conf\target.txt
            TARGET_ARCH           = IA32 X64
            TOOL_CHAIN_TAG        = VS2019
    - edksetup.bat Rebuild
    - edksetup.bat VS2019

Location of UEFI Info Tool code in EDK2:
    - Edit D:\repos\edk2\MdeModulePkg\MdeModulePkg.dsc and add below line under [Components] sections
            a. MdeModulePkg/Application/uefiinfo/uefiinfo.inf

Run build:
    1. D:\repos\edk2> build -a X64 -p MdeModulePkg\MdeModulePkg.dsc

UEFI Info App:
    1. After successful build you should have uefiinfo.efi in D:\repos\edk2\Build\MdeModule\DEBUG_VS2019\X64\

git push vineel_edk2 HEAD:user/vineelko/uefiinfo_port


pip install -r pip-requirements.txt --upgrade
stuart_setup -c .pytool/CISettings.py -p MdeModulePkg -t RELEASE -a X64 TOOL_CHAIN_TAG=VS2019
stuart_update -c .pytool/CISettings.py -p MdeModulePkg -t RELEASE -a X64 TOOL_CHAIN_TAG=VS2019
python BaseTools/Edk2ToolsBuild.py -t VS2019
stuart_ci_build -c .pytool/CISettings.py -p MdeModulePkg -t RELEASE -a X64 TOOL_CHAIN_TAG=VS2019
