# script to auto update head comment
import os
import re
from datetime import datetime

# 定义要添加的注释模板
author_name = "Tianyou Zhao"
section = "ECE6122"
description = "What is the purpose of this file?"

# 获取当前日期并格式化
current_date = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

comment_template = f"""/*
Author: {author_name}
Class: {section}
Last Date Modified: {current_date}
Description:
{description}
*/\n\n"""

# 正则表达式模式，用于匹配现有注释
comment_pattern = re.compile(
    r"/\*\nAuthor:.*?\nClass:.*?\nLast Date Modified:.*?\nDescription:\n.*?\*/",
    re.DOTALL,
)

# 遍历当前目录中的所有文件
for filename in os.listdir("."):
    print(filename)
    if filename.endswith(".cpp"):
        with open(filename, "r", encoding='utf-8') as file:
            content = file.read()
        
        # 检查文件是否包含注释
        match = comment_pattern.search(content)
        
        if match:
            # 如果找到注释，则更新Last Date Modified字段
            updated_comment = re.sub(
                r"(Last Date Modified: ).*",
                r"\1" + current_date,
                match.group(0)
            )
            content = comment_pattern.sub(updated_comment, content)
        else:
            # 如果没有找到注释，则添加新的注释到文件头
            content = comment_template + content
        
        # 将修改后的内容写回文件
        with open(filename, "w") as file:
            file.write(content)

print("操作完成。")
