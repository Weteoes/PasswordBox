<template>
  <div class="dlg2_a">
    <div class="dlg2_aa">
      <div class="dlg2_aaa">
        <div class="dlg2_aaaa">
          <div class="dlg2_title" v-text="dlgTitle"></div>
        </div>
        <div class="dlg2_button">
          <div class="dlg2_onlyButton el-icon-user" @click="menuChangePassword" title="修改密码"></div>
          <div class="dlg2_onlyButton el-icon-switch-button" @click="menuExit" title="退出登录"></div>
          <div class="dlg2_onlyButton el-icon-arrow-down" @click="menuMin" title="隐藏"></div>
        </div>
      </div>
    </div>
    <div class="dlg2_ab">
      <router-view />
    </div>
  </div>
</template>

<style lang="scss" scoped>
* {
  user-select:none;
}

$topHeight: 34px;
.dlg2_a {
  border: 1px solid #c5b9b9;
  min-width: 600px;
  width: 100%;
  box-sizing: border-box;
  //height: 100vh;
}

.dlg2_a > .dlg2_aa {
  width:100%;
  height: $topHeight;
  padding: 3px 0;
  background: #3faffa;
}

.dlg2_a > .dlg2_aa > .dlg2_aaa {
  width: 100%;
  height: 100%;
  display: flex;
}

.dlg2_a > .dlg2_aa >.dlg2_aaa > .dlg2_aaaa {
  flex: 1;
  height: 100%;
}

.dlg2_title {
  height: $topHeight;
  line-height: $topHeight;
  margin-left: 15px;
  font-size: 20px;
  color:#fff;
}

.dlg2_a > .dlg2_aa >.dlg2_aaa > .dlg2_button {
  min-width: 60px;
  height: 100%;
  padding: 0 5px;
  display: flex;
}

.dlg2_button > .dlg2_onlyButton {
  width: 24px;
  height: 24px;
  padding: 5px 5px;
  cursor: pointer;
  color: #fff;
  font-size: 24px;
  margin: 0 auto;
  display: block;
}

.dlg2_ab {
  min-height: 300px;
}
</style>

<script>
export default {
  data () {
    return {
      w: window.weteoes,
      weteoesBrowser: window.weteoesBrowser,
      dlgTitle: 'Title', // 标题
      dlg_aa_menu_if: true // 刷新按钮显示
    }
  },
  methods: {
    ready () {},
    dlgReady () {
      const body = document.querySelector('.dlg2_a')
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
      this.w.softwareApi.app('Main', 'Signout')
    },
    menuChangePassword () {
      this.w.softwareApi.app('Main', 'ShowChangePasswordDlg')
    },
    log (...msg) {
      window.console.log(...msg)
    }
  },
  created () { this.ready() },
  mounted () { this.dlgReady() }
}
</script>
