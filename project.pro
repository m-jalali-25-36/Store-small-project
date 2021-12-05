QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

CMAKE_BUILD_TYPE = Release
# Debug

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        class/DataBaseCategory.cpp \
        class/DataBaseProducts.cpp \
        class/DataBaseUser.cpp \
        class/UnitWorkDb.cpp \
    class/cart.cpp \
        class/category.cpp \
        class/product.cpp \
        class/user.cpp \
    fun/addCategoryPanel.cpp \
    fun/addProductPanel.cpp \
    fun/addUserPanel.cpp \
        fun/customerPanel.cpp \
    fun/editCategoryPanel.cpp \
    fun/editProductPanel.cpp \
    fun/editUserPanel.cpp \
        fun/employeePanel.cpp \
        fun/firstPanel.cpp \
        fun/fun.cpp \
        fun/helpPanel.cpp \
        fun/loginPanel.cpp \
    fun/printProduct.cpp \
    fun/selectCategory.cpp \
        fun/welcome.cpp \
    library/contain.cpp \
    library/delay.cpp \
    library/isCharacter.cpp \
    library/isNumber.cpp \
        library/split.cpp \
        library/toInt.cpp \
        library/toLower.cpp \
        library/trim.cpp \
        main.cpp \
        tools/combine.cpp \
    tools/search.cpp \
        tools/show.cpp \
    tools/sumAmount.cpp \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    out/Product.db \
    out/category.db \
    out/users.db
