SOURCE_PATH = $$PWD

CONFIG(debug, debug|release) {
    DEBUG_RELEASE = DEBUG
} else {
    DEBUG_RELEASE = RELEASE
}

DOCX_LIB_PATH = $$SOURCE_PATH/lib

DOCX_TEST_APP_PATH = $$SOURCE_PATH/bin/$$DEBUG_RELEASE

defineReplace(targetPath) {
    return($$shell_path($$1))
}

# COPY FILES TO A FLODER
defineReplace(copyFile) {
    unset(files)
    unset(dist)
    files = $$1 # files list
    dist = $$targetPath($$2) # target floder
    win32 {
        COPY = copy /y
        MKDIR = mkdir
    } else {
        COPY = cp
        MKDIR = mkdir -p
    }

    for (f, files) {
        #dist_file = $$dist/$$basename(f)
        dist = $$system_path($$dist)
        !exists($$dist):system($$MKDIR $$dist)
        #强制覆盖已存在的 todo linux下需测试
        #!exists($$dist_file): {
            f = $$system_path($$f)
            dist = $$system_path($$dist)
            system($$COPY $$f $$dist)
        #}
    }
    return($$files)
}

CONFIG += c++11
