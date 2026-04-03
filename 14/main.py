subor = open("clanok.txt", "r")

cislice = 0
male = 0
velke = 0
for riadok in subor:
    for znak in riadok.strip():
        if 48 <= ord(znak) <= 57:
            cislice += 1
        elif 97 <= ord(znak) <= 122:
            male += 1
        elif 65 <= ord(znak) <= 90:
            velke += 1

print(f"Numbers: {cislice}")
print(f"Lowecase letters: {male}")
print(f"Uppercase letters: {velke}")

subor.close()
