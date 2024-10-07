package=dbus
$(package)_version=1.10.18
# $(package)_download_path=https://dbus.freedesktop.org/releases/dbus
# https://ipfs.decenomy.net/QmXoHHNbkFZCjzj3cNTcqTEejEd5QEcB2nXixvm43xPc7d?filename=dbus-1.10.18.tar.gz
$(package)_download_path=https://ipfs.decenomy.net
$(package)_download_file=QmXoHHNbkFZCjzj3cNTcqTEejEd5QEcB2nXixvm43xPc7d
$(package)_file_name=$(package)-$($(package)_version).tar.gz
$(package)_sha256_hash=6049ddd5f3f3e2618f615f1faeda0a115104423a7996b7aa73e2f36e38cc514a
$(package)_dependencies=expat

define $(package)_set_vars
  $(package)_config_opts=--disable-tests --disable-doxygen-docs --disable-xml-docs --disable-static --without-x
endef

define $(package)_config_cmds
  $($(package)_autoconf)
endef

define $(package)_build_cmds
  $(MAKE) -C dbus libdbus-1.la
endef

define $(package)_stage_cmds
  $(MAKE) -C dbus DESTDIR=$($(package)_staging_dir) install-libLTLIBRARIES install-dbusincludeHEADERS install-nodist_dbusarchincludeHEADERS && \
  $(MAKE) DESTDIR=$($(package)_staging_dir) install-pkgconfigDATA
endef
