# originally an Alpine package, but isn't Arch the same format?

# Contributor:
# Maintainer: Matthew Brewer <mjbrewer17@gmail.com>
pkgname=ghg
pkgver=1.0.7
pkgrel=0
pkgdesc="Play games on heaphones with volume buttons. Games can be programmed with JSON instructions."
url="https://github.com/matthew-james-brewer/ghg"
arch=("x86_64" "i686" "aarch64" "armv7h")
license=("MPL-2.0")
depends=("cjson" "espeak" "alsa-lib")
makedepends=()
checkdepends=()
install=
subpackages=()
#source=$pkgver.tar.gz
source=("https://github.com/matthew-james-brewer/ghg/releases/download/$pkgver/$pkgver-$pkgname.tar.gz")
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

sha512sums=("dba71b2ba89a1855acd14243ea87a3aa2230ab34c52d27de78280753d501219e2e43f6d929a3c804acc6b281df421d41f515c58d6664363b769210a1dc14e669")
