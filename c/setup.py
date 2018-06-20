from distutils.core import setup, Extension

setup(	name = "total",
	maintainer = "Leonardo Fuso",
	maintainer_email = "some@thing.com",
	ext_modules = [
			Extension(
				'total', sources = ['total.c'],
				extra_compile_args = ['-O0']
				)
		]
)
