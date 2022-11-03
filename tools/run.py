from importlib.machinery import SourceFileLoader

SourceFileLoader("test", "test/common/__init__.py").load_module().run_qemu("i386", "", "kernel/kernel.elf")

