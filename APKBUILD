# originally an Alpine package, but isn't Arch the same format?

# Contributor:
# Maintainer: Matthew Brewer <mjbrewer17@gmail.com>
pkgname=ghg
pkgver=1.0.3
pkgrel=0
pkgdesc="Play games on heaphones with volume buttons. Games can be programmed with JSON instructions."
url="https://github.com/matthew-james-brewer/ghg"
arch=("x86_64" "i686" "aarch64" "armv7h")
license=("MPL-2.0")
depends=("cjson" "espeak-ng" "alsa-lib")
makedepends=()
checkdepends=()
install=
subpackages=()
#source=$pkgver.tar.gz
source=("https://github.com/matthew-james-brewer/ghg/archive/refs/tags/$pkgver.tar.gz")
builddir="$srcdir/"
options=()

build() {
 cd $pkgname-$pkgver
 cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -B b -DCMAKE_INSTALL_PREFIX="$pkgdir/usr"
 cmake --build b
}

package() {
 cd $pkgname-$pkgver
 cmake --install b
}

sha512sums=("7a450d78488ac5557d8b5d05d1fe654685bef2eea2ef10ead94e505c42c7dac182a724cd98a73f9670ade46e4f66730d4ddb578c6363d051037703bb6491e54c $pkgver.tar.gz")
