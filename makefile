CC := gcc
CFLAGS := -Wall -Wextra -g

# 获取所有 .c 文件（排除带 main 的文件）
SRCS := $(wildcard *.c)
MAIN_SRCS := cli.c arrayStack.c  # 明确列出包含 main 的文件
SHARED_SRCS := $(filter-out $(MAIN_SRCS), $(SRCS))

# 生成对应的可执行文件
TARGETS := $(MAIN_SRCS:.c=)  # cli.c -> cli

# 默认目标：编译所有可执行文件
all: $(TARGETS)

# 规则：为每个带 main 的 .c 文件生成可执行文件
$(TARGETS): %: %.c $(SHARED_SRCS)
	$(CC) $(CFLAGS) $^ -o $@

# 清理
clean:
	rm -f $(TARGETS)

