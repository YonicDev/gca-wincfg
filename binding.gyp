{
  "targets": [
    {
      "link_settings": {
        "libraries":["../lib/libwdi.lib"]
      },
      "include_dirs" : [
        "<!(node -e \"require('nan')\")",
	"libwdi/libwdi"
      ],
      "target_name": "gca-wincfg",
      "sources": [ "gca-cfg.cc" ]
    }
  ]
}