package=libevent
$(package)_version=2.1.12-stable
# $(package)_download_path=https://github.com/libevent/libevent/releases/download/release-2.1.12-stable/
# https://ipfs.decenomy.net/QmRSSDnv6BmQRNRNLbVr16cdrNDqThLANm5Hj1fUNt8R3G?filename=libevent-2.1.12-stable.tar.gz
$(package)_download_path=https://ipfs.decenomy.net
$(package)_download_file=QmRSSDnv6BmQRNRNLbVr16cdrNDqThLANm5Hj1fUNt8R3G
$(package)_file_name=libevent-$($(package)_version).tar.gz
$(package)_sha256_hash=92e6de1be9ec176428fd2367677e61ceffc2ee1cb119035037a27d346b0403bb

define $(package)_preprocess_cmds
  ./autogen.sh
endef

define $(package)_set_vars
  $(package)_config_opts=--disable-shared --disable-openssl --disable-libevent-regress --disable-samples
  $(package)_config_opts_release=--disable-debug-mode
  $(package)_config_opts_linux=--with-pic
endef

define $(package)_config_cmds
  $($(package)_autoconf)
endef

define $(package)_build_cmds
  $(MAKE)
endef

define $(package)_stage_cmds
  $(MAKE) DESTDIR=$($(package)_staging_dir) install
endef

define $(package)_postprocess_cmds
endef
