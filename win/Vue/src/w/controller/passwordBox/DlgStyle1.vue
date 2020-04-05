<template>
  <div class="dlg1_a" :style="dlgStyle">
    <div class="dlg1_aa">
      <div class="title" v-text="dlgTitle"></div>
      <div class="dlg1_aa_menu" v-if="dlg_aa_menu_if">
        <!-- <div class="dlg1_aa_menu_" @click="menuMin" id="menu_min"></div> -->
        <div class="dlg1_aa_menu_" @click="menuMin" id="menu_exit"></div>
      </div>
    </div>
    <div class="dlg1_ab">
      <router-view />
    </div>
  </div>
</template>

<style lang="scss" scoped>
* {
  user-select:none;
}

$padding_left: 15px;
.dlg1_a {
  border: 1px solid #c5b9b9;
  min-width: 100px;
  min-height: 100px;
  display: flex;
  flex-direction: column;
  box-sizing: border-box;
}
.dlg1_aa {
  display: flex;
  width: 100%;
  min-height: 30px;
  background: #31acff;
}
.dlg1_aa > .title {
  flex: 1;
  padding: 0 $padding_left;
  line-height: 30px;
  font-size: 15px;
}
.dlg1_aa_menu {
  display: flex;
  min-width: 30px;
}
.dlg1_aa_menu_ {
  width: 30px;
  line-height: 30px;
  text-align: center;
}

.dlg1_aa_menu > #menu_exit:hover {
  background: #f04c46;
}

.dlg1_aa_menu > #menu_exit::before {
  content: "X";
}

.dlg1_aa_menu > #menu_min:hover {
  background: #189df5;
}

.dlg1_aa_menu > #menu_min::before {
  content: "";
  display: block;
  margin: 14px auto;
  width: 12px;
  height: 2px;
  background: #000;
}
.dlg1_ab {
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
      dlgTitle: 'Title', // 标题
      dlgStyle: '', // 样式
      dlg_aa_menu_if: true // 刷新按钮显示
    }
  },
  methods: {
    ready () {},
    dlgReady () {
      const body = document.querySelector('.dlg1_a')
      const w = body.offsetWidth
      const h = body.offsetHeight
      this.w.softwareApi.dlg.size(w, h)
      this.log('width:{0} height:{1}'.format(w, h))
    },
    menuMin () {
      this.dlg_aa_menu_if = false
      this.w.softwareApi.dlg.minimize()
      setTimeout(() => { this.dlg_aa_menu_if = true }, 100)
    },
    menuExit () {
      this.w.softwareApi.dlg.close()
    },
    log (...msg) {
      window.console.log(...msg)
    }
  },
  created () { this.ready() },
  mounted () { this.dlgReady() }
}
</script>
