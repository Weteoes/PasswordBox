<template>
  <div>
    <router-view />
  </div>
</template>

<script>
export default {
  data () {
    return {
      w: window.weteoes,
      weteoesBrowser: window.weteoesBrowser
    }
  },
  methods: {
    ready () {
      this.readySoftwareApi()
      this.readySoftwareDlgApi()
      this.readySoftwareFun()
      this.readyUrl()
    },
    readyUrl () {
      const host = 'http://127.0.0.1:23340'
      this.w.url = {
        get: host + '/operating/browser/get?',
        create: host + '/operating/browser/create?',
        del: host + '/operating/browser/del?',
        getAll: host + '/operating/console/getAll?'
      }
    },
    readySoftwareApi () {
      this.w.softwareApi = {
        dlg: {
          mouse: {
            down: (x, y) => {
              try {
                this.weteoesBrowser.dlg.mouse.down(x, y)
              } catch (e) { this.log(e) }
            },
            move: (x, y) => {
              try {
                this.weteoesBrowser.dlg.mouse.move(x, y)
              } catch (e) { this.log(e) }
            },
            up: () => {
              try {
                this.weteoesBrowser.dlg.mouse.up()
              } catch (e) { this.log(e) }
            }
          },
          size: (width, height) => {
            try {
              this.weteoesBrowser.dlg.size(width, height)
            } catch (e) { this.log(e) }
          },
          minimize: () => {
            try {
              this.weteoesBrowser.dlg.minimize()
            } catch (e) { this.log(e) }
          },
          close: () => {
            try {
              this.weteoesBrowser.dlg.close()
            } catch (e) { this.log(e) }
          }
        },
        app: (app, fun, args) => {
          try {
            return this.weteoesBrowser.app(app, fun, args)
          } catch (e) { this.log(e) }
        }
      }
    },
    readySoftwareDlgApi () {
      const this_ = this
      this.w.softwareDlgApi = {
        // 窗口焦点
        activate_ (nState) {
          this_.debugLog('SoftwareDlgApi activate:{0}'.format(nState))
          this.activate(nState)
        },
        activate: (nState) => { }
      }
    },
    readySoftwareFun () {
      this.w.softwareFun = {
        // 拖动条
        addDlgMouseEvent: a => {
          let status = 0
          a.addEventListener('mousedown', a => {
            if (a.which === 1) {
              status = 1
              const x = a.clientX
              const y = a.clientY
              this.w.softwareApi.dlg.mouse.down(x, y)
            }
          })
          document.addEventListener('mousemove', a => {
            if (status !== 1) {
              return
            }
            const x = a.screenX
            const y = a.screenY
            this.w.softwareApi.dlg.mouse.move(x, y)
          })
          document.addEventListener('mouseup', a => {
            if (status !== 1) {
              return
            }
            status = 0
            this.w.softwareApi.dlg.mouse.up()
          })
        }
      }
    },
    debugLog (...msg) {
      if (this.$store.state.debug) {
        window.console.log(...msg)
      }
    },
    log (...msg) {
      window.console.log(...msg)
    }
  },
  created () {
    this.ready()
  },
  mounted () { }
}
</script>
