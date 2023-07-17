import os
path = 'C:\Dir'
files = os.listdir(path)


for index, file in enumerate(files):
    os.rename(os.path.join(path, file), os.path.join(path, 'pakchunk13_' + file))
