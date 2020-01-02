const addon = require('../build/Debug/gtk-utils')

const test = addon.getSetting("org.gnome.desktop.interface", "gtk-theme")
let start = process.hrtime.bigint()

let result
for  (let i = 0; i < 1000; i++) {
    result = addon.getSetting("org.gnome.desktop.interface", "gtk-theme")
}
let end = process.hrtime.bigint()
console.info(`Execution time: ${((end - start) / BigInt(1000000.0))} ms`)
console.log(result)