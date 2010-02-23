#!/usr/bin/env python
"""
setup.py file for SWIG libvisca
"""

from distutils.core import setup, Extension


libvisca_module = Extension('_libvisca',
                           sources=['visca/libvisca.i'],
                           libraries=['visca'],
                           )

setup (name = 'libvisca',
       version = '0.1',
       author      = "Robert (Jamie) Munro",
       description = """Simple python swig wrapper for libvisca""",
       ext_modules = [libvisca_module],
       package_dir = {'': 'visca'},
       py_modules = ["libvisca"],
       )

