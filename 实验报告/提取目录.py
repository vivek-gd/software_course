import fitz  # PyMuPDF

# 获取用户输入的PDF文件名
input_file = input("请输入OCR输出的PDF文件名（包含扩展名）: ")
doc = fitz.open(input_file)
toc = []

for page_num in range(len(doc)):
    text = doc[page_num].get_text()
    for line in text.splitlines():
        if line.startswith("第") and "章" in line:  # 简单匹配“第X章”
            toc.append([1, line.strip(), page_num + 1])

# 展示生成的目录信息让用户确认
print("生成的目录如下：")
for item in toc:
    print(f"级别: {item[0]}, 标题: {item[1]}, 页码: {item[2]}")
confirm = input("确认此目录信息是否正确？(y/n): ")
if confirm.lower()!= "y":
    print("目录生成已取消。")
else:
    doc.set_toc(toc)
    output_file = input("请输入输出的带目录的PDF文件名（包含扩展名）: ")
    doc.save(output_file)
    print(f"已成功生成带目录的PDF文件：{output_file}")