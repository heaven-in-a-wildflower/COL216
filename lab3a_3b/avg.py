with open("g3.txt", "r") as f:
    lines = f.readlines()

with open("g3_out.txt", "a") as output_file:
    prev_third_field = -1
    avg_list = []
    product = 1
    for line in lines:
        if line.strip():
            if "Miss Ratio:" in line:
                miss_ratio = float(line.split(":")[1].strip())
                avg_list.append(miss_ratio)
            else:
                fields = [int(x) for x in line.split()]
                if fields[2] != prev_third_field:
                    if prev_third_field != -1:
                        avg = sum(avg_list) / len(avg_list)
                        output_file.write(f"avg_{product}_{prev_third_field} = {avg:.6f}\n")
                    avg_list = []
                    product = fields[0] * fields[1] * fields[2]
                    prev_third_field = fields[2]

    if avg_list:
        avg = sum(avg_list) / len(avg_list)
        output_file.write(f"avg_{product}_{prev_third_field} = {avg:.6f}\n")