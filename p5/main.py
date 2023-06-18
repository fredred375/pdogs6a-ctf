
with open("flag.tiff", 'rb') as f:
  content = f.read()
  print(str(content[0]))

output = f"char arr[{len(content)}] = {{"
for b in content:
  output += f"{b}, "
output += "};"
print(output)