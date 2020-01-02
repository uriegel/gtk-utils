const addon = require('./build/Debug/giotest')

const rett = addon.test("org.gnome.desktop.interface", "gtk-theme")
let start = process.hrtime.bigint()

for  (let i = 0; i < 1; i++) {
    const rett = addon.test("org.gnome.desktop.interface", "gtk-theme")
}
let end = process.hrtime.bigint()
console.info(`Execution time getExifDate (hr): ${((end - start) / BigInt(1000000.0))} ms`)


console.log("org.gnome.desktop.interface")