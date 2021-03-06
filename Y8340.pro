QT       += core gui
QT       += widgets
QT       += network
QT       += multimedia

##for arm
#LIBS += -L$$PWD/libusb-1.0.21-arm/libusb/ -lusb-1.0
#INCLUDEPATH += $$PWD/libusb-1.0.21-arm/libusb
#for x86
#LIBS +=  -L$$PWD/libusb-1.0.21-x86/libusb/ -lusb-1.0
#INCLUDEPATH += $$PWD/libusb-1.0.21-x86/libusb
#for x64
#LIBS +=  -L$$PWD/libusb-1.0.21-x64/libusb/ -lusb-1.0
#INCLUDEPATH += $$PWD/libusb-1.0.21-x64/libusb

HEADERS += \   
    uarm10/system_defines_uarm10.h \
    uarm10/status_uarm10.h \
    uarm10/smart_uarm10.h \
    uarm10/skin_uarm10.h \
    uarm10/sim_uarm10.h \
    uarm10/quick_uarm10.h \
    uarm10/motion_uarm10.h \
    uarm10/menu_uarm10.h \
    uarm10/main_uarm10.h \
    uarm10/key_uarm10.h \
    uarm10/film_uarm10.h \
    uarm08/system_defines_uarm8.h \
    uarm08/status_uarm8.h \
    uarm08/smart_uarm8.h \
    uarm08/skin_uarm8.h \
    uarm08/sim_uarm8.h \
    uarm08/quick_uarm8.h \
    uarm08/motion_uarm8.h \
    uarm08/menu_uarm8.h \
    uarm08/main_uarm8.h \
    uarm08/key_uarm8.h \
    uarm08/film_uarm8.h \
    system/system_update.h \
    system/system_speed.h \
    system/system_smart_ndt.h \
    system/system_smart.h \
    system/system_self_run.h \
    system/system_platform.h \
    system/system_password2.h \
    system/system_password.h \
    system/system_network.h \
    system/system_menu.h \
    system/system_light_curtain.h \
    system/system_install2.h \
    system/system_install.h \
    system/system_imepad.h \
    system/system_general.h \
    system/system_defines.h \
    system/system_console1.h \
    system/system_confirm2.h \
    system/system_confirm.h \
    system/system_config.h \
    system/system_client_request.h \
    system/system_advance.h \
    system/sys_database.h \
    system/dialog_confirm.h \
    system/debug_page2.h \
    system/debug_page1.h \
    rf08/system_defines_rf8a.h \
    rf08/main_base_rf8a.h \
    rf08/info_base_rf8a.h \
    rail12/status_rail12.h \
    rail12/smart_rail12.h \
    rail12/skin_rail12.h \
    rail12/sim_rail12.h \
    rail12/quick_rail12.h \
    rail12/motion_rail12.h \
    rail12/menu_rail12.h \
    rail12/main_rail12.h \
    rail12/key_rail12.h \
    rail12/film_rail12.h \
    rail12/system_defines_rail12.h \
    rail08/system_defines_rail8.h \
    rail08/status_rail8.h \
    rail08/smart_rail8.h \
    rail08/skin_rail8.h \
    rail08/sim_rail8.h \
    rail08/quick_rail8.h \
    rail08/motion_rail8.h \
    rail08/menu_rail8.h \
    rail08/main_rail8.h \
    rail08/key_rail8.h \
    rail08/film_rail8.h \
    ndt10/skin_ndt10.h \
    ndt10/net_server_ndt10.h \
    ndt10/net_client_ndt10.h \
    ndt10/motor_ndt10.h \
    ndt10/mech_tube.h \
    ndt10/mech_stand.h \
    ndt10/mech_small_table.h \
    ndt10/mech_round_table.h \
    ndt10/mech_panel_brace.h \
    ndt10/mech_panel.h \
    ndt10/mech_obj.h \
    ndt10/mech_long_table.h \
    ndt10/mech_arm.h \
    ndt10/main_base_ndt10.h \
    ndt10/lcd_number.h \
    ndt10/film_ndt10.h \
    ndt10/exit_base_ndt10.h \
    ndt10/button_render.h \
    ndt10/system_mech.h \
    ndt08/system_defines_ndt8a.h \
    ndt08/skin_ndt8.h \
    ndt08/sim_ndt8.h \
    ndt08/net_server_ndt8.h \
    ndt08/net_client_ndt8.h \
    ndt08/main_base_ndt8.h \
    ndt08/info_base_ndt8.h \
    ndt08/thread_joystick.h \
    #ndt08/libusb-1.0.21/libusb/libusb.h \
    gen/gen_param.h \
    gen/gen_main.h \
    gen/gen_focus.h \
    gen/gen_config.h \
    gen/gen_client.h \
    gen/gen_aec.h \
    ceil10b/system_defines_ceil10b.h \
    ceil10b/status_ceil10b.h \
    ceil10b/smart_ceil10b.h \
    ceil10b/skin_ceil10b.h \
    ceil10b/sim_ceil10b.h \
    ceil10b/quick_ceil10b.h \
    ceil10b/motion_ceil10b.h \
    ceil10b/menu_ceil10b.h \
    ceil10b/main_ceil10b.h \
    ceil10b/key_ceil10b.h \
    ceil10b/film_ceil10b.h \
    ceil10b/fast_ceil10b.h \
    ceil10a/system_defines_ceil10a.h \
    ceil10a/status_ceil10a.h \
    ceil10a/smart_ceil10a.h \
    ceil10a/skin_ceil10a.h \
    ceil10a/sim_ceil10a.h \
    ceil10a/quick_ceil10a.h \
    ceil10a/motion_ceil10a.h \
    ceil10a/menu_ceil10a.h \
    ceil10a/main_ceil10a.h \
    ceil10a/key_ceil10a.h \
    ceil10a/film_ceil10a.h \
    base/title_base.h \
    base/thread_touchscreen.h \
    base/tech_base.h \
    base/task_monitor.h \
    base/task_com_key.h \
    base/task_com_ctrl.h \
    base/task_com_base.h \
    base/task_can.h \
    base/system_base.h \
    base/status_base.h \
    base/smart_base.h \
    base/skin_base.h \
    base/sim_base.h \
    base/remote_base.h \
    base/quick_base.h \
    base/net_server_base.h \
    base/net_client_base.h \
    base/net_base.h \
    base/motor_menu.h \
    base/motor_base.h \
    base/motion_base.h \
    base/menu_base.h \
    base/main_base.h \
    base/label_click.h \
    base/key_base.h \
    base/info_base.h \
    base/film_base.h \
    base/fast_base.h \
    base/face_base.h \
    base/exit_base.h \
    base/debug_base.h \
    base/curtain_base.h \
    base/button_stable.h \
    base08/curtain_base8.h \
    base08/exit_base8.h \
    base08/face_base8.h \
    base08/fast_base8.h \
    base08/film_base8.h \
    base08/info_base8.h \
    base08/key_base8.h \
    base08/main_base8.h \
    base08/menu_base8.h \
    base08/motion_base8.h \
    base08/net_client_base8.h \
    base08/net_server_base8.h \
    base08/quick_base8.h \
    base08/sim_base8.h \
    base08/skin_base8.h \
    base08/smart_base8.h \
    base08/status_base8.h \
    base08/tech_base8.h \
    base08/title_base8.h \
    base10/curtain_base10.h \
    base10/exit_base10.h \
    base10/face_base10.h \
    base10/fast_base10.h \
    base10/film_base10.h \
    base10/info_base10.h \
    base10/key_base10.h \
    base10/main_base10.h \
    base10/menu_base10.h \
    base10/motion_base10.h \
    base10/net_client_base10.h \
    base10/net_server_base10.h \
    base10/quick_base10.h \
    base10/sim_base10.h \
    base10/skin_base10.h \
    base10/smart_base10.h \
    base10/status_base10.h \
    base10/tech_base10.h \
    base10/title_base10.h \
    base12/curtain_base12.h \
    base12/exit_base12.h \
    base12/face_base12.h \
    base12/fast_base12.h \
    base12/film_base12.h \
    base12/info_base12.h \
    base12/key_base12.h \
    base12/main_base12.h \
    base12/menu_base12.h \
    base12/motion_base12.h \
    base12/net_client_base12.h \
    base12/net_server_base12.h \
    base12/quick_base12.h \
    base12/sim_base12.h \
    base12/skin_base12.h \
    base12/smart_base12.h \
    base12/status_base12.h \
    base12/tech_base12.h \
    base12/title_base12.h \
    mgr/curtain_mgr.h \
    mgr/exit_mgr.h \
    mgr/face_mgr.h \
    mgr/fast_mgr.h \
    mgr/film_mgr.h \
    mgr/gen_param_mgr.h \
    mgr/info_mgr.h \
    mgr/key_mgr.h \
    mgr/main_mgr.h \
    mgr/menu_mgr.h \
    mgr/motion_mgr.h \
    mgr/motor_mgr.h \
    mgr/net_mgr.h \
    mgr/quick_mgr.h \
    mgr/sim_mgr.h \
    mgr/skin_mgr.h \
    mgr/smart_mgr.h \
    mgr/status_mgr.h \
    mgr/tech_mgr.h \
    mgr/title_mgr.h \
    main_frame.h \
    main_setting.h \
    remote_client.h \
    remote_server.h \
    resource_manager.h \
    thread_remote_controller.h \
    thread_remote_worker.h \
    ceil08/film_ceil8.h \
    ceil08/key_ceil8.h \
    ceil08/main_ceil8.h \
    ceil08/menu_ceil8.h \
    ceil08/motion_ceil8.h \
    ceil08/quick_ceil8.h \
    ceil08/sim_ceil8.h \
    ceil08/skin_ceil8.h \
    ceil08/smart_ceil8.h \
    ceil08/status_ceil8.h \
    ceil08/system_defines_ceil8.h
SOURCES += \  
    uarm10/status_uarm10.cpp \
    uarm10/smart_uarm10.cpp \
    uarm10/skin_uarm10.cpp \
    uarm10/sim_uarm10.cpp \
    uarm10/quick_uarm10.cpp \
    uarm10/motion_uarm10.cpp \
    uarm10/menu_uarm10.cpp \
    uarm10/main_uarm10.cpp \
    uarm10/key_uarm10.cpp \
    uarm10/film_uarm10.cpp \
    uarm08/status_uarm8.cpp \
    uarm08/smart_uarm8.cpp \
    uarm08/skin_uarm8.cpp \
    uarm08/sim_uarm8.cpp \
    uarm08/quick_uarm8.cpp \
    uarm08/motion_uarm8.cpp \
    uarm08/menu_uarm8.cpp \
    uarm08/main_uarm8.cpp \
    uarm08/key_uarm8.cpp \
    uarm08/film_uarm8.cpp \
    system/system_update.cpp \
    system/system_speed.cpp \
    system/system_smart_ndt.cpp \
    system/system_smart.cpp \
    system/system_self_run.cpp \
    system/system_platform.cpp \
    system/system_password2.cpp \
    system/system_password.cpp \
    system/system_network.cpp \
    system/system_menu.cpp \
    system/system_light_curtain.cpp \
    system/system_install2.cpp \
    system/system_install.cpp \
    system/system_imepad.cpp \
    system/system_general.cpp \
    system/system_defines.cpp \
    system/system_console1.cpp \
    system/system_confirm2.cpp \
    system/system_confirm.cpp \
    system/system_config.cpp \
    system/system_client_request.cpp \
    system/system_advance.cpp \
    system/sys_database.cpp \
    system/dialog_confirm.cpp \
    system/debug_page2.cpp \
    system/debug_page1.cpp \
    rf08/main_base_rf8a.cpp \
    rf08/info_base_rf8a.cpp \
    rail12/status_rail12.cpp \
    rail12/smart_rail12.cpp \
    rail12/skin_rail12.cpp \
    rail12/sim_rail12.cpp \
    rail12/quick_rail12.cpp \
    rail12/motion_rail12.cpp \
    rail12/menu_rail12.cpp \
    rail12/main_rail12.cpp \
    rail12/key_rail12.cpp \
    rail12/film_rail12.cpp \
    rail08/status_rail8.cpp \
    rail08/smart_rail8.cpp \
    rail08/skin_rail8.cpp \
    rail08/sim_rail8.cpp \
    rail08/quick_rail8.cpp \
    rail08/motion_rail8.cpp \
    rail08/menu_rail8.cpp \
    rail08/main_rail8.cpp \
    rail08/key_rail8.cpp \
    rail08/film_rail8.cpp \
    ndt10/skin_ndt10.cpp \
    ndt10/net_server_ndt10.cpp \
    ndt10/net_client_ndt10.cpp \
    ndt10/motor_ndt10.cpp \
    ndt10/mech_tube.cpp \
    ndt10/mech_stand.cpp \
    ndt10/mech_small_table.cpp \
    ndt10/mech_round_table.cpp \
    ndt10/mech_panel_brace.cpp \
    ndt10/mech_panel.cpp \
    ndt10/mech_obj.cpp \
    ndt10/mech_long_table.cpp \
    ndt10/mech_arm.cpp \
    ndt10/main_base_ndt10.cpp \
    ndt10/lcd_number.cpp \
    ndt10/film_ndt10.cpp \
    ndt10/exit_base_ndt10.cpp \
    ndt10/button_render.cpp \
    ndt10/system_mech.cpp \
    ndt08/thread_joystick.cpp \
    #ndt08/libusb-1.0.21/libusb/sync.c \
    #ndt08/libusb-1.0.21/libusb/strerror.c \
    #ndt08/libusb-1.0.21/libusb/io.c \
    #ndt08/libusb-1.0.21/libusb/hotplug.c \
    #ndt08/libusb-1.0.21/libusb/descriptor.c \
    #ndt08/libusb-1.0.21/libusb/core.c \
    #ndt08/libusb-1.0.21/libusb/os/poll_posix.c \
    #ndt08/libusb-1.0.21/libusb/os/threads_posix.c \
    #ndt08/libusb-1.0.21/libusb/os/linux_usbfs.c \
    #ndt08/libusb-1.0.21/libusb/os/linux_netlink.c \
    ndt08/skin_ndt8.cpp \
    ndt08/sim_ndt8.cpp \
    ndt08/net_server_ndt8.cpp \
    ndt08/net_client_ndt8.cpp \
    ndt08/main_base_ndt8.cpp \
    ndt08/info_base_ndt8.cpp \
    gen/gen_param.cpp \
    gen/gen_main.cpp \
    gen/gen_focus.cpp \
    gen/gen_config.cpp \
    gen/gen_client.cpp \
    gen/gen_aec.cpp \
    ceil10b/status_ceil10b.cpp \
    ceil10b/smart_ceil10b.cpp \
    ceil10b/skin_ceil10b.cpp \
    ceil10b/sim_ceil10b.cpp \
    ceil10b/quick_ceil10b.cpp \
    ceil10b/motion_ceil10b.cpp \
    ceil10b/menu_ceil10b.cpp \
    ceil10b/main_ceil10b.cpp \
    ceil10b/key_ceil10b.cpp \
    ceil10b/film_ceil10b.cpp \
    ceil10b/fast_ceil10b.cpp \
    ceil10a/status_ceil10a.cpp \
    ceil10a/smart_ceil10a.cpp \
    ceil10a/skin_ceil10a.cpp \
    ceil10a/sim_ceil10a.cpp \
    ceil10a/quick_ceil10a.cpp \
    ceil10a/motion_ceil10a.cpp \
    ceil10a/menu_ceil10a.cpp \
    ceil10a/main_ceil10a.cpp \
    ceil10a/key_ceil10a.cpp \
    ceil10a/film_ceil10a.cpp \
    base/title_base.cpp \
    base/thread_touchscreen.cpp \
    base/tech_base.cpp \
    base/task_monitor.cpp \
    base/task_com_key.cpp \
    base/task_com_ctrl.cpp \
    base/task_com_base.cpp \
    base/task_can.cpp \
    base/system_base.cpp \
    base/status_base.cpp \
    base/smart_base.cpp \
    base/skin_base.cpp \
    base/sim_base.cpp \
    base/remote_base.cpp \
    base/quick_base.cpp \
    base/net_server_base.cpp \
    base/net_client_base.cpp \
    base/net_base.cpp \
    base/motor_menu.cpp \
    base/motor_base.cpp \
    base/motion_base.cpp \
    base/menu_base.cpp \
    base/main_base.cpp \
    base/label_click.cpp \
    base/key_base.cpp \
    base/info_base.cpp \
    base/film_base.cpp \
    base/fast_base.cpp \
    base/face_base.cpp \
    base/exit_base.cpp \
    base/debug_base.cpp \
    base/curtain_base.cpp \
    base/button_stable.cpp \
    base08/curtain_base8.cpp \
    base08/exit_base8.cpp \
    base08/face_base8.cpp \
    base08/fast_base8.cpp \
    base08/film_base8.cpp \
    base08/info_base8.cpp \
    base08/key_base8.cpp \
    base08/main_base8.cpp \
    base08/menu_base8.cpp \
    base08/motion_base8.cpp \
    base08/net_client_base8.cpp \
    base08/net_server_base8.cpp \
    base08/quick_base8.cpp \
    base08/sim_base8.cpp \
    base08/skin_base8.cpp \
    base08/smart_base8.cpp \
    base08/status_base8.cpp \
    base08/tech_base8.cpp \
    base08/title_base8.cpp \
    base10/curtain_base10.cpp \
    base10/exit_base10.cpp \
    base10/face_base10.cpp \
    base10/fast_base10.cpp \
    base10/film_base10.cpp \
    base10/info_base10.cpp \
    base10/key_base10.cpp \
    base10/main_base10.cpp \
    base10/menu_base10.cpp \
    base10/motion_base10.cpp \
    base10/net_client_base10.cpp \
    base10/net_server_base10.cpp \
    base10/quick_base10.cpp \
    base10/sim_base10.cpp \
    base10/skin_base10.cpp \
    base10/smart_base10.cpp \
    base10/status_base10.cpp \
    base10/tech_base10.cpp \
    base10/title_base10.cpp \
    base12/curtain_base12.cpp \
    base12/exit_base12.cpp \
    base12/face_base12.cpp \
    base12/fast_base12.cpp \
    base12/film_base12.cpp \
    base12/info_base12.cpp \
    base12/key_base12.cpp \
    base12/main_base12.cpp \
    base12/menu_base12.cpp \
    base12/motion_base12.cpp \
    base12/net_client_base12.cpp \
    base12/net_server_base12.cpp \
    base12/quick_base12.cpp \
    base12/sim_base12.cpp \
    base12/skin_base12.cpp \
    base12/smart_base12.cpp \
    base12/status_base12.cpp \
    base12/tech_base12.cpp \
    base12/title_base12.cpp \
    mgr/curtain_mgr.cpp \
    mgr/exit_mgr.cpp \
    mgr/face_mgr.cpp \
    mgr/fast_mgr.cpp \
    mgr/film_mgr.cpp \
    mgr/gen_param_mgr.cpp \
    mgr/info_mgr.cpp \
    mgr/key_mgr.cpp \
    mgr/main_mgr.cpp \
    mgr/menu_mgr.cpp \
    mgr/motion_mgr.cpp \
    mgr/motor_mgr.cpp \
    mgr/net_mgr.cpp \
    mgr/quick_mgr.cpp \
    mgr/sim_mgr.cpp \
    mgr/skin_mgr.cpp \
    mgr/smart_mgr.cpp \
    mgr/status_mgr.cpp \
    mgr/tech_mgr.cpp \
    mgr/title_mgr.cpp \
    main.cpp \
    main_frame.cpp \
    main_setting.cpp \
    remote_client.cpp \
    remote_server.cpp \
    resource_manager.cpp \
    thread_remote_controller.cpp \
    thread_remote_worker.cpp \
    ceil08/film_ceil8.cpp \
    ceil08/key_ceil8.cpp \
    ceil08/main_ceil8.cpp \
    ceil08/menu_ceil8.cpp \
    ceil08/motion_ceil8.cpp \
    ceil08/quick_ceil8.cpp \
    ceil08/sim_ceil8.cpp \
    ceil08/skin_ceil8.cpp \
    ceil08/smart_ceil8.cpp \
    ceil08/status_ceil8.cpp


RESOURCES += \
    Y8330.qrc

OTHER_FILES += \
    w6410.ts \
    w6410_en.ts \
    w6410_kr.ts \
    w6410_ru.ts

TRANSLATIONS += \
    w6410.ts \
    w6410_en.ts \
    w6410_kr.ts \
    w6410_ru.ts

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android


