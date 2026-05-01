# originally an Alpine package, but isn't Arch the same format?

# Contributor:
# Maintainer: Matthew Brewer <mjbrewer17@gmail.com>
pkgname=ghg
pkgver=1.0.5
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

sha512sums=("4fa4017a633f2c840881c77d8608d514275a4a030113f4fc94e88b85413e6d53b336564a41428a41e9e9ccdab2931ea5bbfb6e9a482b787977d29cfaf1756d46")
