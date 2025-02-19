def DelPretinanie(line: str) -> str:
    prepinanie = '''!()-[]{};:'",<>./?@#$%^&*_~\\'''
    for char in prepinanie:
        line = line.replace(char, "")
    return line


line = input()
print(DelPretinanie(line))

