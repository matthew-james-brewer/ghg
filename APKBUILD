# Contributor:
# Maintainer: Matthew Brewer <mjbrewer17@gmail.com>
pkgname=ghg
pkgver=1.0.6
pkgrel=0
pkgdesc="Play games on heaphones with volume buttons. Games can be programmed with JSON instructions."
url="https://github.com/matthew-james-brewer/ghg"
arch="x86_64 i686 aarch64 armv7h"
license="MPL-2.0"
depends="cjson espeak alsa-lib"
makedepends="cmake cjson-dev espeak-dev alsa-lib-dev"
checkdepends=
install=
subpackages=
#source=$pkgver.tar.gz
source="https://github.com/matthew-james-brewer/ghg/releases/download/$pkgver/$pkgver-$pkgname.tar.gz"
builddir="$srcdir/"
options="!check"
# idgaf about tests

build() {
 cd $pkgname-$pkgver
 cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -B b -DCMAKE_INSTALL_PREFIX="$pkgdir/usr"
 cmake --build b
}

package() {
 cd $pkgname-$pkgver
 cmake --install b
 for manpage in $(echo $pkgdir/usr/share/man/*/*); do
  tar czf $manpage.tar.gz $manpage
  rm $manpage
 done
}

sha512sums="402ddac3771e818b71d801d4f6e01aaa5156e8f99cff875f09787edc401da31ee627cc435635bc3da0fdc31de258ebc1aa8ef1b58468a5ada618c9a5dbf659b6  $pkgver-$pkgname.tar.gz"
