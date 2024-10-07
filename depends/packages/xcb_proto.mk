package=xcb_proto
$(package)_version=1.10
# $(package)_download_path=https://xcb.freedesktop.org/dist
# https://ipfs.decenomy.net/QmRzchvXBhLAdZz76GF9ikPVufnKnnnBEyAiDnbuz9TWM2?filename=xcb-proto-1.10.tar.bz2
$(package)_download_path=https://ipfs.decenomy.net
$(package)_download_file=QmRzchvXBhLAdZz76GF9ikPVufnKnnnBEyAiDnbuz9TWM2
$(package)_file_name=xcb-proto-$($(package)_version).tar.bz2
$(package)_sha256_hash=7ef40ddd855b750bc597d2a435da21e55e502a0fefa85b274f2c922800baaf05

define $(package)_set_vars
  $(package)_config_opts=--disable-shared
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
  find -name "*.pyc" -delete && \
  find -name "*.pyo" -delete
endef
