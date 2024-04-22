import os  # 导入os模块，用于操作文件和目录  
import shutil  # 导入shutil模块，用于文件操作如复制  
  
def split(split_num, input_path, output_dir):  # 定义一个名为split的函数，用于划分文件  
    # 参数split_num是划分的子文件夹数量，input_path是输入文件夹路径，output_dir是输出文件夹路径  
  
    os.makedirs(output_dir, exist_ok=True)  # 如果输出目录不存在则创建它  
  
    # 创建split_num个输出子文件夹，用于存放划分的文件  
    for i in range(split_num):  
        output_dir_seed = os.path.join(output_dir, str(i))  # 构建子文件夹路径  
        os.makedirs(output_dir_seed, exist_ok=True)  # 创建子文件夹  
  
        # 清除之前可能存在的文件，这里有一个逻辑错误，因为刚创建的目录是空的，所以下面的代码实际上不会执行任何操作  
        #files = [f for f in os.listdir(output_dir_seed) if f.endswith('.jpg') or f.endswith('.png')]  
        files = [f for f in os.listdir(output_dir_seed)]  # 获取子文件夹中所有文件的列表  
        for image_file in files:  # 遍历文件列表  
            os.remove(os.path.join(output_dir_seed, image_file))  # 删除文件  
            print(image_file, '被清理')  # 打印被清理的文件名  
  
    # 获取输入文件夹中所有文件的列表  
    #image_files = [f for f in os.listdir(input_path) if f.endswith('.jpg') or f.endswith('.png')]  
    image_files = [f for f in os.listdir(input_path)]  # 获取所有文件，不区分图片格式  
  
    # 计算每个子文件夹应该存放的文件平均数（向上取整）  
    mean = int(len(image_files) / split_num) + 1  
  
    count = 0  # 用于记录当前正在写入的子文件夹索引  
    count_file = 0  # 用于记录当前子文件夹中已经存放的文件数  
  
    # 遍历输入文件夹中的每个文件  
    for img_file in image_files:  
        output_dir_seed = os.path.join(output_dir, str(count))  # 获取当前要写入的子文件夹路径  
        src_file = os.path.join(input_path, img_file)  # 构建源文件路径  
        dst_file = os.path.join(output_dir_seed, img_file)  # 构建目标文件路径  
  
        # 检查源文件是否为一个文件（而不是子文件夹）  
        if os.path.isfile(src_file):  
            # 将源文件复制到目标子文件夹  
            print(src_file)  # 打印正在复制的文件路径  
            shutil.copy2(src_file, dst_file)  # 复制文件  
  
            count_file += 1  # 当前子文件夹文件数加1  
  
            # 如果当前子文件夹文件数达到平均数，则切换到下一个子文件夹  
            if count_file >= mean:  
                count += 1  # 子文件夹索引加1  
                count_file = 0  # 重置当前子文件夹文件数 













