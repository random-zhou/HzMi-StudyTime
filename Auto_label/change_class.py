import os  
  
# 定义一个函数，用于更改指定路径下所有.txt文件中的类名  
def change_class(class_path, class_name):  
    # 获取class_path路径下所有以.txt结尾的文件列表，这些文件被视为标签训练集  
    label_files = [f for f in os.listdir(class_path) if f.endswith('.txt')]  
  
    # 遍历每一个标签文件  
    for lanel_file in label_files:  
        # 如果文件名是'classes.txt'，则跳过不处理  
        if lanel_file == 'classes.txt':  
            continue  
  
        # 初始化一个变量a，用于存储文件的所有行  
        a = 0  
  
        # 打开文件，以只读模式读取文件内容，并设置编码为utf-8  
        fp = open(os.path.join(class_path, lanel_file), mode='r', encoding='utf-8')  
  
        # 读取文件的所有行，并存储在变量a中  
        a = fp.readlines()  
  
        # 关闭文件  
        fp.close()  
  
        # 重新打开同一个文件，但这次是以写入模式打开  
        fp = open(os.path.join(class_path, lanel_file), mode='w', encoding='utf-8')  
  
        # 初始化一个空字符串s，用于拼接修改后的内容  
        s = ''  
  
        # 遍历文件中的每一行  
        for i in a:  
            # 将每一行的第一个字符替换为新的类名，然后拼接上该行剩余的字符  
            d = str(class_name) + i[1:]  
  
            # 将修改后的行内容添加到字符串s中  
            s = s + d  
  
        # 将修改后的内容写回文件  
        fp.write(s)  
  
        # 关闭文件  
        fp.close()

    