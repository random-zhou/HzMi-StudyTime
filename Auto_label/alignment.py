#确保图片文件和标签文件一一对应,并删除多余文件

import os  
  
def alignment(img_path, label_path, cl_de=False):  
    """  
    函数功能：对齐图片文件和标签文件，确保二者一一对应。  
    参数：  
    - img_path: 图片文件所在的目录路径。  
    - label_path: 标签文件所在的目录路径。  
    - cl_de: 布尔值，默认为False。当为True时，不会删除名为'classes.txt'的文件。  
    """  
  
    # 获取图片路径下所有的jpg或png文件  
    image_files = [f for f in os.listdir(img_path) if f.endswith('.jpg') or f.endswith('.png')]    
  
    # 获取标签路径下所有的txt文件  
    label_files = [f for f in os.listdir(label_path) if f.endswith('.txt')]  
  
    # 遍历标签文件列表  
    for label_file in label_files:  # 如果标签文件多于图片文件  
        # 如果标签文件名为'classes.txt'且cl_de为False，则跳过不处理  
        if label_file == 'classes.txt' and not cl_de:  
            continue  
  
        # 获取标签文件名（不包含扩展名）  
        l_file, _ = os.path.splitext(label_file)  
  
        # 构造对应的图片文件名（基于标签文件名，仅扩展名不同）  
        img_file = l_file + '.jpg'  
  
        # 如果构造的图片文件名不在图片文件列表中  
        if img_file not in image_files:  
            # 删除对应的标签文件  
            os.remove(os.path.join(label_path, label_file))  
            # 打印删除操作信息  
            print(os.path.join(label_path, label_file), '多', "被删除")  
  
    # 遍历图片文件列表  
    for image_file in image_files:  # 如果图片文件多于标签文件  
        # 注意：这里有一个拼写错误，应该是 'image_file' 而不是 'iamge_file'  
        img_file, _ = os.path.splitext(image_file)  # 修正拼写错误  
  
        # 构造对应的标签文件名（基于图片文件名，仅扩展名不同）  
        l_file = img_file + '.txt'  
  
        # 如果构造的标签文件名不在标签文件列表中  
        if l_file not in label_files:  
            # 删除对应的图片文件  
            os.remove(os.path.join(img_path, image_file))  # 同样修正拼写错误  
            # 打印删除操作信息  
            print(os.path.join(img_path, image_file), '多', "被删除")  # 修正拼写错误  

