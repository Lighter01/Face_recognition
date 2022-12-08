TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG += qt
QT += core
QT += gui




SOURCES += \
        _Image.cpp \
        histogram_method.cpp \
        lbph_method.cpp \
        main.cpp \
        random_pixels_method.cpp \
        recognition_call.cpp \
        scaling_method.cpp \
        voting_method.cpp

HEADERS += \
    _Image.h \
    all_libraries.h \
    histogram_method.h \
    lbph_method.h \
    random_pixels_method.h \
    recognition_call.h \
    scaling_method.h \
    voting_method.h

DISTFILES += \
    AT&T_grayscale_normilized/s1/1.pgm \
    AT&T_grayscale_normilized/s1/10.pgm \
    AT&T_grayscale_normilized/s1/2.pgm \
    AT&T_grayscale_normilized/s1/3.pgm \
    AT&T_grayscale_normilized/s1/4.pgm \
    AT&T_grayscale_normilized/s1/5.pgm \
    AT&T_grayscale_normilized/s1/6.pgm \
    AT&T_grayscale_normilized/s1/7.pgm \
    AT&T_grayscale_normilized/s1/8.pgm \
    AT&T_grayscale_normilized/s1/9.pgm \
    AT&T_grayscale_normilized/s10/1.pgm \
    AT&T_grayscale_normilized/s10/10.pgm \
    AT&T_grayscale_normilized/s10/2.pgm \
    AT&T_grayscale_normilized/s10/3.pgm \
    AT&T_grayscale_normilized/s10/4.pgm \
    AT&T_grayscale_normilized/s10/5.pgm \
    AT&T_grayscale_normilized/s10/6.pgm \
    AT&T_grayscale_normilized/s10/7.pgm \
    AT&T_grayscale_normilized/s10/8.pgm \
    AT&T_grayscale_normilized/s10/9.pgm \
    AT&T_grayscale_normilized/s11/1.pgm \
    AT&T_grayscale_normilized/s11/10.pgm \
    AT&T_grayscale_normilized/s11/2.pgm \
    AT&T_grayscale_normilized/s11/3.pgm \
    AT&T_grayscale_normilized/s11/4.pgm \
    AT&T_grayscale_normilized/s11/5.pgm \
    AT&T_grayscale_normilized/s11/6.pgm \
    AT&T_grayscale_normilized/s11/7.pgm \
    AT&T_grayscale_normilized/s11/8.pgm \
    AT&T_grayscale_normilized/s11/9.pgm \
    AT&T_grayscale_normilized/s12/1.pgm \
    AT&T_grayscale_normilized/s12/10.pgm \
    AT&T_grayscale_normilized/s12/2.pgm \
    AT&T_grayscale_normilized/s12/3.pgm \
    AT&T_grayscale_normilized/s12/4.pgm \
    AT&T_grayscale_normilized/s12/5.pgm \
    AT&T_grayscale_normilized/s12/6.pgm \
    AT&T_grayscale_normilized/s12/7.pgm \
    AT&T_grayscale_normilized/s12/8.pgm \
    AT&T_grayscale_normilized/s12/9.pgm \
    AT&T_grayscale_normilized/s13/1.pgm \
    AT&T_grayscale_normilized/s13/10.pgm \
    AT&T_grayscale_normilized/s13/2.pgm \
    AT&T_grayscale_normilized/s13/3.pgm \
    AT&T_grayscale_normilized/s13/4.pgm \
    AT&T_grayscale_normilized/s13/5.pgm \
    AT&T_grayscale_normilized/s13/6.pgm \
    AT&T_grayscale_normilized/s13/7.pgm \
    AT&T_grayscale_normilized/s13/8.pgm \
    AT&T_grayscale_normilized/s13/9.pgm \
    AT&T_grayscale_normilized/s14/1.pgm \
    AT&T_grayscale_normilized/s14/10.pgm \
    AT&T_grayscale_normilized/s14/2.pgm \
    AT&T_grayscale_normilized/s14/3.pgm \
    AT&T_grayscale_normilized/s14/4.pgm \
    AT&T_grayscale_normilized/s14/5.pgm \
    AT&T_grayscale_normilized/s14/6.pgm \
    AT&T_grayscale_normilized/s14/7.pgm \
    AT&T_grayscale_normilized/s14/8.pgm \
    AT&T_grayscale_normilized/s14/9.pgm \
    AT&T_grayscale_normilized/s15/1.pgm \
    AT&T_grayscale_normilized/s15/10.pgm \
    AT&T_grayscale_normilized/s15/2.pgm \
    AT&T_grayscale_normilized/s15/3.pgm \
    AT&T_grayscale_normilized/s15/4.pgm \
    AT&T_grayscale_normilized/s15/5.pgm \
    AT&T_grayscale_normilized/s15/6.pgm \
    AT&T_grayscale_normilized/s15/7.pgm \
    AT&T_grayscale_normilized/s15/8.pgm \
    AT&T_grayscale_normilized/s15/9.pgm \
    AT&T_grayscale_normilized/s16/1.pgm \
    AT&T_grayscale_normilized/s16/10.pgm \
    AT&T_grayscale_normilized/s16/2.pgm \
    AT&T_grayscale_normilized/s16/3.pgm \
    AT&T_grayscale_normilized/s16/4.pgm \
    AT&T_grayscale_normilized/s16/5.pgm \
    AT&T_grayscale_normilized/s16/6.pgm \
    AT&T_grayscale_normilized/s16/7.pgm \
    AT&T_grayscale_normilized/s16/8.pgm \
    AT&T_grayscale_normilized/s16/9.pgm \
    AT&T_grayscale_normilized/s17/1.pgm \
    AT&T_grayscale_normilized/s17/10.pgm \
    AT&T_grayscale_normilized/s17/2.pgm \
    AT&T_grayscale_normilized/s17/3.pgm \
    AT&T_grayscale_normilized/s17/4.pgm \
    AT&T_grayscale_normilized/s17/5.pgm \
    AT&T_grayscale_normilized/s17/6.pgm \
    AT&T_grayscale_normilized/s17/7.pgm \
    AT&T_grayscale_normilized/s17/8.pgm \
    AT&T_grayscale_normilized/s17/9.pgm \
    AT&T_grayscale_normilized/s18/1.pgm \
    AT&T_grayscale_normilized/s18/10.pgm \
    AT&T_grayscale_normilized/s18/2.pgm \
    AT&T_grayscale_normilized/s18/3.pgm \
    AT&T_grayscale_normilized/s18/4.pgm \
    AT&T_grayscale_normilized/s18/5.pgm \
    AT&T_grayscale_normilized/s18/6.pgm \
    AT&T_grayscale_normilized/s18/7.pgm \
    AT&T_grayscale_normilized/s18/8.pgm \
    AT&T_grayscale_normilized/s18/9.pgm \
    AT&T_grayscale_normilized/s19/1.pgm \
    AT&T_grayscale_normilized/s19/10.pgm \
    AT&T_grayscale_normilized/s19/2.pgm \
    AT&T_grayscale_normilized/s19/3.pgm \
    AT&T_grayscale_normilized/s19/4.pgm \
    AT&T_grayscale_normilized/s19/5.pgm \
    AT&T_grayscale_normilized/s19/6.pgm \
    AT&T_grayscale_normilized/s19/7.pgm \
    AT&T_grayscale_normilized/s19/8.pgm \
    AT&T_grayscale_normilized/s19/9.pgm \
    AT&T_grayscale_normilized/s2/1.pgm \
    AT&T_grayscale_normilized/s2/10.pgm \
    AT&T_grayscale_normilized/s2/2.pgm \
    AT&T_grayscale_normilized/s2/3.pgm \
    AT&T_grayscale_normilized/s2/4.pgm \
    AT&T_grayscale_normilized/s2/5.pgm \
    AT&T_grayscale_normilized/s2/6.pgm \
    AT&T_grayscale_normilized/s2/7.pgm \
    AT&T_grayscale_normilized/s2/8.pgm \
    AT&T_grayscale_normilized/s2/9.pgm \
    AT&T_grayscale_normilized/s20/1.pgm \
    AT&T_grayscale_normilized/s20/10.pgm \
    AT&T_grayscale_normilized/s20/2.pgm \
    AT&T_grayscale_normilized/s20/3.pgm \
    AT&T_grayscale_normilized/s20/4.pgm \
    AT&T_grayscale_normilized/s20/5.pgm \
    AT&T_grayscale_normilized/s20/6.pgm \
    AT&T_grayscale_normilized/s20/7.pgm \
    AT&T_grayscale_normilized/s20/8.pgm \
    AT&T_grayscale_normilized/s20/9.pgm \
    AT&T_grayscale_normilized/s21/1.pgm \
    AT&T_grayscale_normilized/s21/10.pgm \
    AT&T_grayscale_normilized/s21/2.pgm \
    AT&T_grayscale_normilized/s21/3.pgm \
    AT&T_grayscale_normilized/s21/4.pgm \
    AT&T_grayscale_normilized/s21/5.pgm \
    AT&T_grayscale_normilized/s21/6.pgm \
    AT&T_grayscale_normilized/s21/7.pgm \
    AT&T_grayscale_normilized/s21/8.pgm \
    AT&T_grayscale_normilized/s21/9.pgm \
    AT&T_grayscale_normilized/s22/1.pgm \
    AT&T_grayscale_normilized/s22/10.pgm \
    AT&T_grayscale_normilized/s22/2.pgm \
    AT&T_grayscale_normilized/s22/3.pgm \
    AT&T_grayscale_normilized/s22/4.pgm \
    AT&T_grayscale_normilized/s22/5.pgm \
    AT&T_grayscale_normilized/s22/6.pgm \
    AT&T_grayscale_normilized/s22/7.pgm \
    AT&T_grayscale_normilized/s22/8.pgm \
    AT&T_grayscale_normilized/s22/9.pgm \
    AT&T_grayscale_normilized/s23/1.pgm \
    AT&T_grayscale_normilized/s23/10.pgm \
    AT&T_grayscale_normilized/s23/2.pgm \
    AT&T_grayscale_normilized/s23/3.pgm \
    AT&T_grayscale_normilized/s23/4.pgm \
    AT&T_grayscale_normilized/s23/5.pgm \
    AT&T_grayscale_normilized/s23/6.pgm \
    AT&T_grayscale_normilized/s23/7.pgm \
    AT&T_grayscale_normilized/s23/8.pgm \
    AT&T_grayscale_normilized/s23/9.pgm \
    AT&T_grayscale_normilized/s24/1.pgm \
    AT&T_grayscale_normilized/s24/10.pgm \
    AT&T_grayscale_normilized/s24/2.pgm \
    AT&T_grayscale_normilized/s24/3.pgm \
    AT&T_grayscale_normilized/s24/4.pgm \
    AT&T_grayscale_normilized/s24/5.pgm \
    AT&T_grayscale_normilized/s24/6.pgm \
    AT&T_grayscale_normilized/s24/7.pgm \
    AT&T_grayscale_normilized/s24/8.pgm \
    AT&T_grayscale_normilized/s24/9.pgm \
    AT&T_grayscale_normilized/s25/1.pgm \
    AT&T_grayscale_normilized/s25/10.pgm \
    AT&T_grayscale_normilized/s25/2.pgm \
    AT&T_grayscale_normilized/s25/3.pgm \
    AT&T_grayscale_normilized/s25/4.pgm \
    AT&T_grayscale_normilized/s25/5.pgm \
    AT&T_grayscale_normilized/s25/6.pgm \
    AT&T_grayscale_normilized/s25/7.pgm \
    AT&T_grayscale_normilized/s25/8.pgm \
    AT&T_grayscale_normilized/s25/9.pgm \
    AT&T_grayscale_normilized/s26/1.pgm \
    AT&T_grayscale_normilized/s26/10.pgm \
    AT&T_grayscale_normilized/s26/2.pgm \
    AT&T_grayscale_normilized/s26/3.pgm \
    AT&T_grayscale_normilized/s26/4.pgm \
    AT&T_grayscale_normilized/s26/5.pgm \
    AT&T_grayscale_normilized/s26/6.pgm \
    AT&T_grayscale_normilized/s26/7.pgm \
    AT&T_grayscale_normilized/s26/8.pgm \
    AT&T_grayscale_normilized/s26/9.pgm \
    AT&T_grayscale_normilized/s27/1.pgm \
    AT&T_grayscale_normilized/s27/10.pgm \
    AT&T_grayscale_normilized/s27/2.pgm \
    AT&T_grayscale_normilized/s27/3.pgm \
    AT&T_grayscale_normilized/s27/4.pgm \
    AT&T_grayscale_normilized/s27/5.pgm \
    AT&T_grayscale_normilized/s27/6.pgm \
    AT&T_grayscale_normilized/s27/7.pgm \
    AT&T_grayscale_normilized/s27/8.pgm \
    AT&T_grayscale_normilized/s27/9.pgm \
    AT&T_grayscale_normilized/s28/1.pgm \
    AT&T_grayscale_normilized/s28/10.pgm \
    AT&T_grayscale_normilized/s28/2.pgm \
    AT&T_grayscale_normilized/s28/3.pgm \
    AT&T_grayscale_normilized/s28/4.pgm \
    AT&T_grayscale_normilized/s28/5.pgm \
    AT&T_grayscale_normilized/s28/6.pgm \
    AT&T_grayscale_normilized/s28/7.pgm \
    AT&T_grayscale_normilized/s28/8.pgm \
    AT&T_grayscale_normilized/s28/9.pgm \
    AT&T_grayscale_normilized/s29/1.pgm \
    AT&T_grayscale_normilized/s29/10.pgm \
    AT&T_grayscale_normilized/s29/2.pgm \
    AT&T_grayscale_normilized/s29/3.pgm \
    AT&T_grayscale_normilized/s29/4.pgm \
    AT&T_grayscale_normilized/s29/5.pgm \
    AT&T_grayscale_normilized/s29/6.pgm \
    AT&T_grayscale_normilized/s29/7.pgm \
    AT&T_grayscale_normilized/s29/8.pgm \
    AT&T_grayscale_normilized/s29/9.pgm \
    AT&T_grayscale_normilized/s3/1.pgm \
    AT&T_grayscale_normilized/s3/10.pgm \
    AT&T_grayscale_normilized/s3/2.pgm \
    AT&T_grayscale_normilized/s3/3.pgm \
    AT&T_grayscale_normilized/s3/4.pgm \
    AT&T_grayscale_normilized/s3/5.pgm \
    AT&T_grayscale_normilized/s3/6.pgm \
    AT&T_grayscale_normilized/s3/7.pgm \
    AT&T_grayscale_normilized/s3/8.pgm \
    AT&T_grayscale_normilized/s3/9.pgm \
    AT&T_grayscale_normilized/s30/1.pgm \
    AT&T_grayscale_normilized/s30/10.pgm \
    AT&T_grayscale_normilized/s30/2.pgm \
    AT&T_grayscale_normilized/s30/3.pgm \
    AT&T_grayscale_normilized/s30/4.pgm \
    AT&T_grayscale_normilized/s30/5.pgm \
    AT&T_grayscale_normilized/s30/6.pgm \
    AT&T_grayscale_normilized/s30/7.pgm \
    AT&T_grayscale_normilized/s30/8.pgm \
    AT&T_grayscale_normilized/s30/9.pgm \
    AT&T_grayscale_normilized/s31/1.pgm \
    AT&T_grayscale_normilized/s31/10.pgm \
    AT&T_grayscale_normilized/s31/2.pgm \
    AT&T_grayscale_normilized/s31/3.pgm \
    AT&T_grayscale_normilized/s31/4.pgm \
    AT&T_grayscale_normilized/s31/5.pgm \
    AT&T_grayscale_normilized/s31/6.pgm \
    AT&T_grayscale_normilized/s31/7.pgm \
    AT&T_grayscale_normilized/s31/8.pgm \
    AT&T_grayscale_normilized/s31/9.pgm \
    AT&T_grayscale_normilized/s32/1.pgm \
    AT&T_grayscale_normilized/s32/10.pgm \
    AT&T_grayscale_normilized/s32/2.pgm \
    AT&T_grayscale_normilized/s32/3.pgm \
    AT&T_grayscale_normilized/s32/4.pgm \
    AT&T_grayscale_normilized/s32/5.pgm \
    AT&T_grayscale_normilized/s32/6.pgm \
    AT&T_grayscale_normilized/s32/7.pgm \
    AT&T_grayscale_normilized/s32/8.pgm \
    AT&T_grayscale_normilized/s32/9.pgm \
    AT&T_grayscale_normilized/s33/1.pgm \
    AT&T_grayscale_normilized/s33/10.pgm \
    AT&T_grayscale_normilized/s33/2.pgm \
    AT&T_grayscale_normilized/s33/3.pgm \
    AT&T_grayscale_normilized/s33/4.pgm \
    AT&T_grayscale_normilized/s33/5.pgm \
    AT&T_grayscale_normilized/s33/6.pgm \
    AT&T_grayscale_normilized/s33/7.pgm \
    AT&T_grayscale_normilized/s33/8.pgm \
    AT&T_grayscale_normilized/s33/9.pgm \
    AT&T_grayscale_normilized/s34/1.pgm \
    AT&T_grayscale_normilized/s34/10.pgm \
    AT&T_grayscale_normilized/s34/2.pgm \
    AT&T_grayscale_normilized/s34/3.pgm \
    AT&T_grayscale_normilized/s34/4.pgm \
    AT&T_grayscale_normilized/s34/5.pgm \
    AT&T_grayscale_normilized/s34/6.pgm \
    AT&T_grayscale_normilized/s34/7.pgm \
    AT&T_grayscale_normilized/s34/8.pgm \
    AT&T_grayscale_normilized/s34/9.pgm \
    AT&T_grayscale_normilized/s35/1.pgm \
    AT&T_grayscale_normilized/s35/10.pgm \
    AT&T_grayscale_normilized/s35/2.pgm \
    AT&T_grayscale_normilized/s35/3.pgm \
    AT&T_grayscale_normilized/s35/4.pgm \
    AT&T_grayscale_normilized/s35/5.pgm \
    AT&T_grayscale_normilized/s35/6.pgm \
    AT&T_grayscale_normilized/s35/7.pgm \
    AT&T_grayscale_normilized/s35/8.pgm \
    AT&T_grayscale_normilized/s35/9.pgm \
    AT&T_grayscale_normilized/s36/1.pgm \
    AT&T_grayscale_normilized/s36/10.pgm \
    AT&T_grayscale_normilized/s36/2.pgm \
    AT&T_grayscale_normilized/s36/3.pgm \
    AT&T_grayscale_normilized/s36/4.pgm \
    AT&T_grayscale_normilized/s36/5.pgm \
    AT&T_grayscale_normilized/s36/6.pgm \
    AT&T_grayscale_normilized/s36/7.pgm \
    AT&T_grayscale_normilized/s36/8.pgm \
    AT&T_grayscale_normilized/s36/9.pgm \
    AT&T_grayscale_normilized/s37/1.pgm \
    AT&T_grayscale_normilized/s37/10.pgm \
    AT&T_grayscale_normilized/s37/2.pgm \
    AT&T_grayscale_normilized/s37/3.pgm \
    AT&T_grayscale_normilized/s37/4.pgm \
    AT&T_grayscale_normilized/s37/5.pgm \
    AT&T_grayscale_normilized/s37/6.pgm \
    AT&T_grayscale_normilized/s37/7.pgm \
    AT&T_grayscale_normilized/s37/8.pgm \
    AT&T_grayscale_normilized/s37/9.pgm \
    AT&T_grayscale_normilized/s38/1.pgm \
    AT&T_grayscale_normilized/s38/10.pgm \
    AT&T_grayscale_normilized/s38/2.pgm \
    AT&T_grayscale_normilized/s38/3.pgm \
    AT&T_grayscale_normilized/s38/4.pgm \
    AT&T_grayscale_normilized/s38/5.pgm \
    AT&T_grayscale_normilized/s38/6.pgm \
    AT&T_grayscale_normilized/s38/7.pgm \
    AT&T_grayscale_normilized/s38/8.pgm \
    AT&T_grayscale_normilized/s38/9.pgm \
    AT&T_grayscale_normilized/s39/1.pgm \
    AT&T_grayscale_normilized/s39/10.pgm \
    AT&T_grayscale_normilized/s39/2.pgm \
    AT&T_grayscale_normilized/s39/3.pgm \
    AT&T_grayscale_normilized/s39/4.pgm \
    AT&T_grayscale_normilized/s39/5.pgm \
    AT&T_grayscale_normilized/s39/6.pgm \
    AT&T_grayscale_normilized/s39/7.pgm \
    AT&T_grayscale_normilized/s39/8.pgm \
    AT&T_grayscale_normilized/s39/9.pgm \
    AT&T_grayscale_normilized/s4/1.pgm \
    AT&T_grayscale_normilized/s4/10.pgm \
    AT&T_grayscale_normilized/s4/2.pgm \
    AT&T_grayscale_normilized/s4/3.pgm \
    AT&T_grayscale_normilized/s4/4.pgm \
    AT&T_grayscale_normilized/s4/5.pgm \
    AT&T_grayscale_normilized/s4/6.pgm \
    AT&T_grayscale_normilized/s4/7.pgm \
    AT&T_grayscale_normilized/s4/8.pgm \
    AT&T_grayscale_normilized/s4/9.pgm \
    AT&T_grayscale_normilized/s40/1.pgm \
    AT&T_grayscale_normilized/s40/10.pgm \
    AT&T_grayscale_normilized/s40/2.pgm \
    AT&T_grayscale_normilized/s40/3.pgm \
    AT&T_grayscale_normilized/s40/4.pgm \
    AT&T_grayscale_normilized/s40/5.pgm \
    AT&T_grayscale_normilized/s40/6.pgm \
    AT&T_grayscale_normilized/s40/7.pgm \
    AT&T_grayscale_normilized/s40/8.pgm \
    AT&T_grayscale_normilized/s40/9.pgm \
    AT&T_grayscale_normilized/s5/1.pgm \
    AT&T_grayscale_normilized/s5/10.pgm \
    AT&T_grayscale_normilized/s5/2.pgm \
    AT&T_grayscale_normilized/s5/3.pgm \
    AT&T_grayscale_normilized/s5/4.pgm \
    AT&T_grayscale_normilized/s5/5.pgm \
    AT&T_grayscale_normilized/s5/6.pgm \
    AT&T_grayscale_normilized/s5/7.pgm \
    AT&T_grayscale_normilized/s5/8.pgm \
    AT&T_grayscale_normilized/s5/9.pgm \
    AT&T_grayscale_normilized/s6/1.pgm \
    AT&T_grayscale_normilized/s6/10.pgm \
    AT&T_grayscale_normilized/s6/2.pgm \
    AT&T_grayscale_normilized/s6/3.pgm \
    AT&T_grayscale_normilized/s6/4.pgm \
    AT&T_grayscale_normilized/s6/5.pgm \
    AT&T_grayscale_normilized/s6/6.pgm \
    AT&T_grayscale_normilized/s6/7.pgm \
    AT&T_grayscale_normilized/s6/8.pgm \
    AT&T_grayscale_normilized/s6/9.pgm \
    AT&T_grayscale_normilized/s7/1.pgm \
    AT&T_grayscale_normilized/s7/10.pgm \
    AT&T_grayscale_normilized/s7/2.pgm \
    AT&T_grayscale_normilized/s7/3.pgm \
    AT&T_grayscale_normilized/s7/4.pgm \
    AT&T_grayscale_normilized/s7/5.pgm \
    AT&T_grayscale_normilized/s7/6.pgm \
    AT&T_grayscale_normilized/s7/7.pgm \
    AT&T_grayscale_normilized/s7/8.pgm \
    AT&T_grayscale_normilized/s7/9.pgm \
    AT&T_grayscale_normilized/s8/1.pgm \
    AT&T_grayscale_normilized/s8/10.pgm \
    AT&T_grayscale_normilized/s8/2.pgm \
    AT&T_grayscale_normilized/s8/3.pgm \
    AT&T_grayscale_normilized/s8/4.pgm \
    AT&T_grayscale_normilized/s8/5.pgm \
    AT&T_grayscale_normilized/s8/6.pgm \
    AT&T_grayscale_normilized/s8/7.pgm \
    AT&T_grayscale_normilized/s8/8.pgm \
    AT&T_grayscale_normilized/s8/9.pgm \
    AT&T_grayscale_normilized/s9/1.pgm \
    AT&T_grayscale_normilized/s9/10.pgm \
    AT&T_grayscale_normilized/s9/2.pgm \
    AT&T_grayscale_normilized/s9/3.pgm \
    AT&T_grayscale_normilized/s9/4.pgm \
    AT&T_grayscale_normilized/s9/5.pgm \
    AT&T_grayscale_normilized/s9/6.pgm \
    AT&T_grayscale_normilized/s9/7.pgm \
    AT&T_grayscale_normilized/s9/8.pgm \
    AT&T_grayscale_normilized/s9/9.pgm
