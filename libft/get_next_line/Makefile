# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/27 16:05:50 by yhadhadi          #+#    #+#              #
#    Updated: 2024/06/05 01:54:27 by yhadhadi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Toolchain and flags
CC := cc
CFLAGS := -Wall -Werror -Wextra -O3 -I../
AR := ar
ARFLAGS := rcs

# Build directories
BUILDDIR := ../build/addons/get_next_line
OBJSDIR := $(BUILDDIR)/main
OBJSDIR_BONUS := $(BUILDDIR)/bonus
OBJSDIRS := $(OBJSDIR) $(OBJSDIR_BONUS)

# Mandatory files
SRCS := get_next_line.c\
	get_next_line_utils.c
OBJS := $(SRCS:%.c=$(OBJSDIR)/%.o)
MARKER := $(BUILDDIR)/.baselined

# Bonus files
SRCS_BONUS := get_next_line_bonus.c\
	get_next_line_utils_bonus.c
OBJS_BONUS := $(SRCS_BONUS:%.c=$(OBJSDIR_BONUS)/%.o)
MARKER_BONUS := $(BUILDDIR)/.bonused

# Main target
NAME := libgnl.a
TARGET := $(BUILDDIR)/$(NAME)
PSEUDO_TARGET := $(MARKER)

# Bonus target
TARGET_BONUS := $(MARKER_BONUS)

# Default target
.DEFAULT_GOAL := $(PSEUDO_TARGET)

# Build main target
$(PSEUDO_TARGET): $(OBJS)
	@rm -f $(MARKER_BONUS)
	@rm -f $(TARGET)
	$(AR) $(ARFLAGS) $(TARGET) $?
	@touch $(MARKER)

# Build bonus target
$(TARGET_BONUS): $(OBJS_BONUS)
	@rm -f $(MARKER)
	@rm -f $(TARGET)
	$(AR) $(ARFLAGS) $(TARGET) $?
	@touch $(MARKER_BONUS)

# Compile source files to object files
$(OBJSDIR)/%.o: %.c | $(OBJSDIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJSDIR_BONUS)/%.o: %.c | $(OBJSDIR_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directories
$(OBJSDIRS):
	@mkdir -p $@

# Intermediate files
.SECONDARY: $(OBJS) $(OBJS_BONUS)

# Phony targets
.PHONY: bonus all clean fclean re

# Add bonus files to the main target
bonus: $(TARGET_BONUS)

# Build main target with bonus included
all: bonus

# Clean object files
clean:
	rm -f $(OBJS) $(OBJS_BONUS)

# Clean all
fclean: clean
	rm -rf $(BUILDDIR)

# Clean slate rebuild
re: fclean all
