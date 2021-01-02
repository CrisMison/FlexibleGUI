include $(ROOTDIR)/build/make.rules

CURDIR  = $(shell pwd)
SUBDIRS = $(shell find $(CURDIR) -maxdepth 3 -type d)  
SRCS 	= $(foreach dir, $(SUBDIRS), $(wildcard $(dir)/*.c))  
OBJS	= $(patsubst %.c, %.o, $(SRCS)) 

ifdef CONFIG_LIB_STATIC
TARGET 	= $(LIBSDIR)/libfgui.a
else
TARGET	= $(LIBSDIR)/libfgui.so
endif

all: $(TARGET) 

$(TARGET):$(OBJS)
ifdef CONFIG_LIB_STATIC
	@$(STEP_LD_STATIC)
else
	@$(STEP_LD_DYM)
endif

$(OBJS): %.o : %.c
	@$(STEP_CC)

clean:
	-@ $(shell find . -name *.o | xargs rm -rf)
	-@ $(shell find . -name *.a | xargs rm -rf)
	-@ $(shell find . -name *.so | xargs rm -rf)


