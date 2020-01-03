{
    "targets": [{
        "target_name": "gtk-utils",
        'conditions': [
            ['OS=="linux"', {
                "sources": [ 
                    'addon.cpp',
                ],
                'include_dirs': [
                    "<!@(node -p \"require('node-addon-api').include\")"
                ],
                'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
                "libraries": ["<!@(pkg-config --libs gio-2.0)"],
                "cflags": [
                    "-Wall", 
                    "-std=c++17",
                    "<!@(pkg-config --cflags gio-2.0)"
                ],
                'cflags_cc': [
                    "-Wall", 
                    "-std=c++17",
                    "<!@(pkg-config --cflags gio-2.0)"
                ],
                'cflags!': [ '-fno-exceptions' ],
                'cflags_cc!': [ '-fno-exceptions' ],
                "ldflags": ["<!@(pkg-config --libs gio-2.0)"],
                'link_settings': {
                    "libraries": [ 
                    ]
                }
            }
        ]]          
    }]
}