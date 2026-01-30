import os
import subprocess
from docx2python import docx2python


def extract_images(docx_path, output_folder):
    """
    从Word文档中提取图片并保存到指定文件夹
    """
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    docx_content = docx2python(docx_path)
    for filename, content in docx_content.images.items():
        img_path = os.path.join(output_folder, filename)
        with open(img_path, 'wb') as f:
            f.write(content)


def convert_word_to_custom_latex(docx_path, template_path, output_folder):
    """
    使用pandoc将Word文档转换为符合特定模板的LaTeX格式
    """
    # 生成临时的 LaTeX 文件路径
    temp_output_filename = os.path.splitext(os.path.basename(docx_path))[0] + "_temp.tex"
    temp_output_path = os.path.join(output_folder, temp_output_filename)
    # 生成最终输出的 LaTeX 文件路径
    output_filename = os.path.splitext(os.path.basename(docx_path))[0] + ".tex"
    output_path = os.path.join(output_folder, output_filename)
    # 指定 pandoc 的完整路径
    pandoc_path = r"D:\Desktop\task\download\pandoc-3.6.4-windows-x86_64\pandoc-3.6.4\pandoc.exe"

    try:
        # 使用pandoc将Word转换为临时的LaTeX文件
        subprocess.run([pandoc_path, docx_path, '-o', temp_output_path], check=True)

        # 读取临时LaTeX文件内容
        with open(temp_output_path, 'r', encoding='utf-8') as temp_file:
            word_converted_content = temp_file.read()

        # 读取封面模板文件内容
        with open(template_path, 'r', encoding='utf-8') as template_file:
            template_content = template_file.read()

        # 找到模板中\begin{document}和\end{document}的位置
        start_index = template_content.find(r'\begin{document}')
        end_index = template_content.find(r'\end{document}')

        # 组合内容
        new_content = template_content[:start_index + len(r'\begin{document}')] + "\n" + word_converted_content + "\n" + \
                      template_content[end_index:]

        # 修改图片路径，使其指向figure文件夹
        figure_folder = os.path.join(os.path.basename(os.path.dirname(output_path)), "figure") + "/"
        new_content = new_content.replace(r"\includegraphics{", r"\includegraphics{" + figure_folder)

        # 写入最终的LaTeX文件
        with open(output_path, 'w', encoding='utf-8') as output_file:
            output_file.write(new_content)

        # 删除临时文件
        os.remove(temp_output_path)

        print(f"Successfully converted {docx_path} to {output_path}")
    except subprocess.CalledProcessError as e:
        print(f"Error converting document: {e}")
    except FileNotFoundError:
        print(f"Pandoc可执行文件未找到，请检查路径: {pandoc_path}")
    except Exception as ex:
        print(f"An unexpected error occurred: {ex}")


if __name__ == "__main__":
    docx_file = "D:\Desktop\电子书&课件\数据库\实验报告\第三次\数据库第三次实验.docx"
    template_file = "D:\\Desktop\\电子书&课件\\数据库\\实验报告\\模板.tex"  # 替换为你的LaTeX封面模板文件路径
    output_folderp = "D:\\Desktop\\电子书&课件\\数据库\\实验报告\\第三次\\figure"
    output_folder = "D:\\Desktop\\电子书&课件\\数据库\\实验报告\\第三次"
    extract_images(docx_file, output_folderp)
    convert_word_to_custom_latex(docx_file, template_file,output_folder)
