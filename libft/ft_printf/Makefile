# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 00:40:09 by yhadhadi          #+#    #+#              #
#    Updated: 2024/06/07 04:17:13 by yhadhadi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Toolchain and flags
CC := cc
CFLAGS := -Wall -Werror -Wextra -O3 -I../ -DNO_LIBFTPRINTF_BONUS
CFLAGS_BONUS := $(filter-out -DNO_LIBFTPRINTF_BONUS, $(CFLAGS))
AR := ar
ARFLAGS := rcs

# Build directories
BUILDDIR := ../build/addons/ft_printf
OBJSDIR := $(BUILDDIR)/main
OBJSDIR_BONUS := $(BUILDDIR)/bonus
OBJSDIRS := $(OBJSDIR) $(OBJSDIR_BONUS)

# Mandatory directories and files
SRCS := ft_printf.c\
	ft_vasprintf_compositor.c\
	ft_vasprintf_formatter.c\
	ft_vasprintf_parser.c\
	ft_vasprintf_stubs.c\
	ft_vasprintf.c\
	ft_vprintf_fd.c
OBJS := $(SRCS:%.c=$(OBJSDIR)/%.o)

# Bonus files
SRCS_BONUS := ft_vasprintf_formatter.c\
	ft_vasprintf_modifier_bonus.c\
	ft_vasprintf_stubs_bonus.c
OBJS_BONUS := $(SRCS_BONUS:%.c=$(OBJSDIR_BONUS)/%.o)
MARKER_BONUS := $(BUILDDIR)/.bonused

# Main target
NAME := libftprintf.a
TARGET := $(BUILDDIR)/$(NAME)

# Bonus target
TARGET_BONUS := $(MARKER_BONUS)

# Default target
.DEFAULT_GOAL := $(TARGET)

# Build main target
$(TARGET): $(OBJS)
	$(AR) $(ARFLAGS) $@ $?

# Build bonus target
$(TARGET_BONUS): $(OBJS_BONUS)
	$(AR) $(ARFLAGS) $(TARGET) $?
	@touch $(MARKER_BONUS)

# Compile source files to object files
$(OBJSDIR)/%.o: %.c | $(OBJSDIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJSDIR_BONUS)/%.o: %.c | $(OBJSDIR_BONUS)
	$(CC) $(CFLAGS_BONUS) -c $< -o $@

# Create build directories
$(OBJSDIRS):
	@mkdir -p $@

# Intermediate files
.SECONDARY: $(OBJS) $(OBJS_BONUS)

# Phony targets
.PHONY: libft bonus all clean fclean re

# Add bonus files to the main target
bonus: $(TARGET) $(TARGET_BONUS)

# Build all targets
all: bonus

# Clean object files
clean:
	rm -f $(OBJS) $(OBJS_BONUS)

# Clean all
fclean: clean
	rm -rf $(BUILDDIR)


# Clean slate rebuild
re: fclean all
