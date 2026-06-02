# Contributor:
# Maintainer: Matthew Brewer <mjbrewer17@gmail.com>
pkgname=ghg
pkgver=1.0.9
pkgrel=0
pkgdesc="Play games on heaphones with volume buttons. Games can be programmed with JSON instructions."
url="http://libhacker.cc/static/ghg/ghg.html"
arch="x86_64 i686 aarch64 armv7h"
license="MPL-2.0"
depends="cjson espeak alsa-lib"
makedepends="cmake cjson-dev espeak-dev alsa-lib-dev"
checkdepends=
install=
subpackages=
#source=$pkgver.tar.gz
source="http://libhacker.cc/static/ghg/release/$pkgver/$pkgver-$pkgname.tar.gz"
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

sha512sums="8fabc401b06778df0bcc098e5889ce1afd6eeebeb3b8860e19e47a154c81ba4071c75d6a3fbd5285bad09fddd8b8774736e97c593d10b9c6cb8e7f9a8aff91d9  $pkgver-$pkgname.tar.gz"
