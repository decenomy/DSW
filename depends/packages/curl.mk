package=curl
$(package)_version=8_4_0
$(package)_download_path=https://github.com/curl/curl/archive/refs/tags/
#$(package)_download_path=https://github.com/decenomy/depends/raw/main/
$(package)_file_name=$(package)-$($(package)_version).tar.gz
$(package)_sha256_hash=5f7097e27b00e54d5522d80c0d44899084a226e9372a0d5d799ad3125dd4b8c0

define $(package)_set_vars
  $(package)_config_opts=--prefix=$($(package)_staging_dir)
endef

define $(package)_build_cmds
  $(MAKE)
  $(MAKE) install
endef
