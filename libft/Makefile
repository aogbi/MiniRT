# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 00:40:09 by yhadhadi          #+#    #+#              #
#    Updated: 2025/01/02 03:18:31 by aogbi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Toolchain and flags
CC := cc
CFLAGS := -Wall -Werror -Wextra -O3 -DNO_LIBFT_BONUS -DNO_LIBFT_ADDONS -fPIC
CFLAGS_BONUS := $(filter-out -DNO_LIBFT_BONUS,$(CFLAGS))
AR := ar
ARFLAGS := -M
PARTIALS_ARFLAGS := rcs

# Build directories
BUILDDIR := build
BUILDDIR_ADDONS := $(BUILDDIR)/addons
OBJSDIR := $(BUILDDIR)/main
OBJSDIR_BONUS := $(BUILDDIR)/bonus
OBJSDIRS := $(OBJSDIR) $(OBJSDIR_BONUS)

# Build state persistence file
BUILD_STATE := $(BUILDDIR)/build_state.mk
-include $(BUILD_STATE)

# Mandatory files
SRCS := ft_abs.c\
	ft_atoi.c\
	ft_atol.c\
	ft_bzero.c\
	ft_calloc.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isgraph.c\
	ft_isprint.c\
	ft_ispunct.c\
	ft_isspace.c\
	ft_itoa_base.c\
	ft_itoa.c\
	ft_labs.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_memset.c\
	ft_memswap.c\
	ft_putchar_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_putstr_fd.c\
	ft_radix.c\
	ft_split.c\
	ft_strchr.c\
	ft_strcmp.c\
	ft_strcspn.c\
	ft_strdup.c\
	ft_striteri.c\
	ft_strjoin.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_strlen.c\
	ft_strmapi.c\
	ft_strncmp.c\
	ft_strnstr.c\
	ft_strpbrk.c\
	ft_strrchr.c\
	ft_strrev.c\
	ft_strspn.c\
	ft_strtrim.c\
	ft_substr.c\
	ft_tolower.c\
	ft_toupper.c\
	ft_ultoa_base.c\
	ft_utoa_base.c\
	ft_utoa.c\
	ft_vstriteri.c\
	ft_atod.c
OBJS := $(SRCS:%.c=$(OBJSDIR)/%.o)

# Bonus files
SRCS_BONUS := ft_lstadd_back_bonus.c\
	ft_lstadd_front_bonus.c\
	ft_lstclear_bonus.c\
	ft_lstdelone_bonus.c\
	ft_lstiter_bonus.c\
	ft_lstlast_bonus.c\
	ft_lstmap_bonus.c\
	ft_lstnew_bonus.c\
	ft_lstsize_bonus.c\
	ft_stackclear_bonus.c\
	ft_stacknew_bonus.c\
	ft_stackpeek_bonus.c\
	ft_stackpop_bonus.c\
	ft_stackpop_first_bonus.c\
	ft_stackpush_bonus.c\
	ft_stackpush_back_bonus.c\
	ft_stackrot_bonus.c\
	ft_stackrrot_bonus.c\
	ft_stackswap_bonus.c
OBJS_BONUS := $(SRCS_BONUS:%.c=$(OBJSDIR_BONUS)/%.o)

# Main target
NAME := libft.a
TARGET := $(NAME)
PARTIAL_TARGET = $(BUILDDIR)/libft.a
PARTIAL_TARGETS ?= $(PARTIAL_TARGET)
define append_partial
$(filter-out $(1),$(PARTIAL_TARGETS)) $(1)
endef

# Bonus target
TARGET_BONUS := $(BUILDDIR)/libft_bonus.a

# Addon targets
TARGET_ADDONS := $(BUILDDIR_ADDONS)/get_next_line/libgnl.a\
	$(BUILDDIR_ADDONS)/ft_printf/libftprintf.a

# Build scripts target
TARGET_MRI := $(BUILDDIR)/libft.mri

# Default target
.DEFAULT_GOAL := $(TARGET)

# Build main target
$(TARGET): $(TARGET_MRI)
	$(AR) $(ARFLAGS) < $(TARGET_MRI)
$(PARTIAL_TARGET): $(OBJS)
	$(AR) $(PARTIALS_ARFLAGS) $@ $?

# Build bonus target
$(TARGET_BONUS): $(OBJS_BONUS)
	$(AR) $(PARTIALS_ARFLAGS) $@ $?

# Compile source files to object files
$(OBJSDIR)/%.o: %.c | $(OBJSDIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJSDIR_BONUS)/%.o: %.c | $(OBJSDIR_BONUS)
	$(CC) $(CFLAGS_BONUS) -c $< -o $@

# Build addons
$(TARGET_ADDONS):
	$(MAKE) -C $(lastword $(subst /, ,$(@D)))

# Create MRI scripts
$(TARGET_MRI): $(PARTIAL_TARGETS)
	@touch $(TARGET_MRI)
	@echo "CREATE libft.a\n\
	$(foreach partial,$(PARTIAL_TARGETS), ADDLIB $(partial)\n)\
	SAVE\n\
	END" > $(TARGET_MRI)

# Create build directories
$(OBJSDIRS):
	@mkdir -p $@

# Intermediate files
.SECONDARY: $(OBJS) $(OBJS_BONUS)

# Phony targets
.PHONY: bonus all addons clean fclean re

# Add bonus files to the main target
bonus: PARTIAL_TARGETS := $(call append_partial,$(TARGET_BONUS))
bonus:
	$(MAKE) PARTIAL_TARGETS="$(PARTIAL_TARGETS)" $(TARGET)
	@echo "PARTIAL_TARGETS = $(PARTIAL_TARGETS)" > $(BUILD_STATE)

# Add addons files to the main target
addons: PARTIAL_TARGETS := $(call append_partial,$(TARGET_ADDONS))
addons:
	$(MAKE) PARTIAL_TARGETS="$(PARTIAL_TARGETS)" $(TARGET)
	@echo "PARTIAL_TARGETS = $(PARTIAL_TARGETS)" > $(BUILD_STATE)

# Build main target with bonus included
all: 
	$(MAKE) bonus
	$(MAKE) addons

# Clean object files
clean:
	rm -f $(OBJS) $(OBJS_BONUS)

# Clean all
fclean: clean
	rm -rf $(BUILDDIR)
	rm -f $(TARGET)

# Clean slate rebuild
re: fclean all
