csv = open('to_sort.csv', 'r')
rows = csv.readlines()
csv.close()

stats = {}

if len(rows) > 1:
    keys = rows[0].split(',')
    #print(keys)
    values = rows[1].split(',')
    size = min(len(keys), len(values))
    for i in range(0, size):
        #print(keys[i], " : ", values[i])
        value = values[i].replace(".", ",")
        try:
            stats.update({ keys[i] : float(values[i]) })
        except:
            pass
            # ignore

sorted_keys = sorted(stats, key=stats.get)
sorted_keys.reverse()
sorted_stats = {}
for key in sorted_keys:
    sorted_stats[key] = stats[key]

out = open('processed.csv', 'w')
for key, value in sorted_stats.items():
    if value < 0.00000000000001:
        break;
    out.write(key)
    out.write(";")
    out.write(str(value).replace(".", ","))
    out.write('\n')
out.close();

for key, value in sorted_stats.items():
    if value < 0.01:
        break;
    print(key, " : ", value)




    
        



            
