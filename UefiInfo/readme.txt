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
    - pip install -r pip-requirements.txt --upgrade

Launch build environment:
set PATH=D:\tools\iasl;%PATH%
set PYTHON_HOME=%localappdata%\Programs\Python\Python311
set NASM_PREFIX=D:\tools\nasm\
set CLANG_BIN=C:\Program Files\LLVM\bin\
edksetup.bat VS2019
edit Conf\target.txt
    TARGET_ARCH           = IA32 X64
    TOOL_CHAIN_TAG        = VS2019
edksetup.bat Rebuild
edksetup.bat VS2019


Source code location:
Edit D:\repos\edk2\UefiInfo\UefiInfo.dsc and add below line under [Components] sections
    uefiinfo/uefiinfo.inf

Run build(complete platform):
D:\repos\edk2> build -a X64 -p UefiInfo\UefiInfo.dsc

Run build(only the module):
D:\repos\edk2> build -a X64 -m UefiInfo\UefiInfo.inf

UEFI Info App:
After successful build the uefiinfo.efi will be in D:\repos\edk2\Build\UefiInfo\DEBUG_VS2019\X64\


git push origin HEAD:uefiinfo


Linux
sudo apt install build-essential uuid-dev iasl git  nasm  python-is-python3
make -C BaseTools
. edksetup.sh
micro Conf/target.txt
    TARGET_ARCH           = IA32 X64
    TOOL_CHAIN_TAG        = GCC5

build -a X64 -p UefiInfo/UefiInfo.dsc









stuart_setup -c .pytool/CISettings.py -p MdeModulePkg -t RELEASE -a X64 TOOL_CHAIN_TAG=VS2019
stuart_update -c .pytool/CISettings.py -p MdeModulePkg -t RELEASE -a X64 TOOL_CHAIN_TAG=VS2019
python BaseTools/Edk2ToolsBuild.py -t VS2019
stuart_ci_build -c .pytool/CISettings.py -p MdeModulePkg -t RELEASE -a X64 TOOL_CHAIN_TAG=VS2019
