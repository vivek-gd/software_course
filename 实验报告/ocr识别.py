from paddleocr import PaddleOCR, draw_ocr
from reportlab.pdfgen import canvas
from reportlab.lib.pagesizes import letter
from PyPDF2 import PdfReader, PdfWriter
import os

# 交互式输入原始PDF文件路径
input_pdf_path = input("请输入原始PDF文件的路径: ")
# 交互式输入输出OCR版本PDF文件路径
output_pdf_path = input("请输入输出OCR版本PDF文件的路径: ")

# 初始化OCR模型
ocr = PaddleOCR(use_angle_cls=True, lang='ch')

# 读取PDF文件并进行OCR识别
result = ocr.ocr(input_pdf_path, cls=True)

# 临时存储识别结果的文本文件路径
temp_text_file = 'temp_ocr_result.txt'
with open(temp_text_file, 'w', encoding='utf-8') as f:
    for page_result in result:
        for line in page_result:
            text = line[1][0]
            f.write(text + '\n')

# 获取原始PDF的页数和页面尺寸
reader = PdfReader(input_pdf_path)
num_pages = len(reader.pages)
page_width, page_height = letter

# 创建新的PDF写入对象
writer = PdfWriter()

# 遍历每一页，将识别的文字添加到新的PDF中
for page_num in range(num_pages):
    page = reader.pages[page_num]
    packet = open("temp_page.pdf", "wb")
    can = canvas.Canvas(packet, pagesize=(page_width, page_height))

    # 从临时文本文件中读取文字内容并添加到当前页
    with open(temp_text_file, 'r', encoding='utf-8') as f:
        lines = f.readlines()
        y = page_height - 50  # 初始y坐标
        for line in lines:
            can.drawString(50, y, line.strip())  # 简单设置起始x坐标为50，y坐标递减
            y -= 20  # 假设每行文字高度为20，可根据实际情况调整

    can.save()
    packet.close()

    new_page = PdfReader("temp_page.pdf").pages[0]
    new_page.merge_page(page)
    writer.add_page(new_page)

    os.remove("temp_page.pdf")

# 输出最终的OCR版本PDF
with open(output_pdf_path, 'wb') as output_file:
    writer.write(output_file)

# 删除临时文本文件
os.remove(temp_text_file)

print(f"已生成OCR版本的PDF文件: {output_pdf_path}")
