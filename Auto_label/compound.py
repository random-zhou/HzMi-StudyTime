import os  
import shutil  

def compound(input_dir, output_path):  
    """  
    将指定输入目录(input_dir)下的所有子目录中的文件复制到指定的输出路径(output_path)。  
      
    参数:  
    input_dir (str): 输入目录的路径。  
    output_path (str): 输出路径，用于存放复制的文件。  
    """  
    # 获取input_dir下所有的子目录列表  
    subdirs = [os.path.join(input_dir, name) for name in os.listdir(input_dir) if os.path.isdir(os.path.join(input_dir, name))]  
  
    # 遍历每一个子目录  
    for subdir in subdirs:  
        # 获取subdir目录下所有的文件列表（不限制文件类型）  
        image_files = [f for f in os.listdir(subdir)]  
  
        # 遍历每一个文件  
        for img_file in image_files:  
            # 构造源文件（即需要复制的文件）的完整路径  
            src_file = os.path.join(subdir, img_file)  
  
            # 构造目标文件（即复制到output_path的文件）的完整路径  
            dst_file = os.path.join(output_path, img_file)  
  
            # 确保src_file确实是一个文件（而不是目录）  
            if os.path.isfile(src_file):  
                # 打印源文件路径，便于追踪  
                print(src_file)  
  
                # 使用shutil.copy2复制文件，同时保留文件的元数据（如时间戳）  
                shutil.copy2(src_file, dst_file)
        

