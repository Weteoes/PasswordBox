<template>
  <div class="dlg_a">
    <div class="dlg_aa">
      <div class="title" v-text="dlgTitle"></div>
      <div class="dlg_aa_menu">
        <div class="dlg_aa_menu_" @click="menuMin" id="menu_min"></div>
        <div class="dlg_aa_menu_" @click="menuExit" id="menu_exit"></div>
      </div>
    </div>
    <div class="dlg_ab">
      <router-view />
    </div>
  </div>
</template>

<style lang="scss">
$padding_left: 15px;
.dlg_a {
  border: 1px solid #000;
  min-width: 300px;
  min-height: 200px;
  display: flex;
  flex-direction: column;
  box-sizing: border-box;
}
.dlg_aa {
  display: flex;
  width: 100%;
  min-height: 30px;
  background: #31acff;
}
.dlg_aa > .title {
  flex: 1;
  padding: 0 $padding_left;
  line-height: 30px;
  font-size: 15px;
}
.dlg_aa_menu {
  display: flex;
  min-width: 30px;
}
.dlg_aa_menu_ {
  width: 30px;
  line-height: 30px;
  text-align: center;
}

.dlg_aa_menu > #menu_exit:hover {
  background: #f04c46;
}

.dlg_aa_menu > #menu_exit::before {
  content: "X";
}

.dlg_aa_menu > #menu_min:hover {
  background: #189df5;
}

.dlg_aa_menu > #menu_min::before {
  content: "";
  display: block;
  margin: 14px auto;
  width: 12px;
  height: 2px;
  background: #000;
}
.dlg_ab {
  flex: 1;
  width: auto;
  min-height: 30px;
  padding: $padding_left;
}
</style>

<script>
export default {
  data () {
    return {
      w: window.weteoes,
      weteoesBrowser: window.weteoesBrowser,
      dlgTitle: 'Title'
    }
  },
  methods: {
    ready () {
      this.readySoftwareApi()
      this.readySoftwareFun()
    },
    dlgReady () {
      const body = document.querySelector('.dlg_a')
      const w = body.offsetWidth
      const h = body.offsetHeight
      console.log(w, h)
      this.w.softwareApi.dlg.size(w, h)
    },
    menuMin () {
      alert('Min')
    },
    menuExit () {
      alert('Exit')
    },
    readySoftwareApi () {
      this.w.softwareApi = {
        dlg: {
          mouse: {
            down (x, y) {
              try {
                this.weteoesBrowser.dlg.mouse.down(x, y)
              } catch (e) {}
            },
            move (x, y) {
              try {
                this.weteoesBrowser.dlg.mouse.move(x, y)
              } catch (e) {}
            },
            up () {
              try {
                this.weteoesBrowser.dlg.mouse.up()
              } catch (e) {}
            }
          },
          size (width, height) {
            try {
              this.weteoesBrowser.size(width, height)
            } catch (e) {}
          }
        }
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
    }
  },
  created () {
    this.ready()
  },
  mounted () {
    this.dlgReady()
  }
}
</script>
