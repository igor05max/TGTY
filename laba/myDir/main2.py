from PIL import Image

img = Image.open("img.png")

pixel_mass = img.load()

width, height = img.size
print(width, height)
for j in range(height):
    for i in range(width // 2):
        pixel_mass[i, j], pixel_mass[width - i - 1, j] = pixel_mass[width - i - 1, j], pixel_mass[i, j]

img2 = img
img2.save("img2.png")


# img2 = img.transpose(Transpose.FLIP_LEFT_RIGHT)
# img2.save("img2.png")
