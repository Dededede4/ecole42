#/usr/local/bin/python3

import settings
import sys
def file_get_contents(filename):
	try:
		with open(filename, 'r') as f:
			return f.read()
	except Exception:
			print("Input file error")
			sys.exit();

if __name__ == '__main__':
	if (len(sys.argv) != 2):
		print("Bad arguments")
		sys.exit()
	if (sys.argv[1][-9:] != ".template"):
		print("Bad extention")
		sys.exit()
	content = file_get_contents(sys.argv[1])
	for name in dir(settings):
		try:
			content = content.replace("{%s}" % (name), getattr(settings, name))
		except Exception:
			pass
	try:
		file = open("file.html","w")
		file.write(content)
		file.close();
	except Exception:
		print("Output file error")
		sys.exit();