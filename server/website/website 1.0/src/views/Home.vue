<template>
  <div id="Home">
    <nav>
      <el-menu
        :default-active="navNowSelect"
        class="el-menu-demo"
        mode="horizontal"
        @select="navSelectHandle"
      >
        <el-menu-item>
          <div class="logo">
            <img src="@/assets/logo.png" />
            <span>密码保管箱 ( Password Box )</span>
          </div>
        </el-menu-item>
        <el-menu-item index="GitHub">GitHub</el-menu-item>
      </el-menu>
      <a ref="GitHub" href="https://github.com/Weteoes/PasswordBox" target="_blank"></a>
    </nav>
    <div class="step">
      <!-- Step0 -->
      <div class="onlyStep">
        <div class="png"><img draggable="false" src="@/assets/step0.png"/></div>
        <div class="data onlyStepData">
          <div class="data">
            <div class="title">密码保管箱</div>
            <div class="text">界面简洁，无广告</div>
            <div class="text">基于Chrome插件、CEF、VueCli制作</div>
            <div class="text">如有任何建议，可邮件: mail@weteoes.cn</div>
            <div class="downloadData">
              <div class="title">立即下载</div>
              <div class="downloadBuuton">
                <el-button @click="downloadBuuton('browser')">浏览器插件</el-button>
                <el-button @click="downloadBuuton('win')">客户端</el-button>
              </div>
            </div>
          </div>
        </div>
      </div>
      <!-- Step1 -->
      <div class="onlyStep">
        <div class="data onlyStepData">
          <div class="data">
            <div class="title">AES256加密模式</div>
            <div class="text">AES256加密后，只有在正确输入密码的情况下，数据才会被程序正确解读，如果密码丢失，数据将无法恢复。</div>
          </div>
        </div>
        <div class="png"><img draggable="false" src="@/assets/step1.png"/></div>
      </div>
      <!-- Step2 -->
      <div class="onlyStep">
        <div class="png"><img draggable="false" src="@/assets/step2.png"/></div>
        <div class="data onlyStepData">
          <div class="data">
            <div class="title">本地工作模式</div>
            <div class="text">本地工作，数据将通过AES256加密后保存本地，数据更加安全。</div>
          </div>
        </div>
      </div>
      <!-- Step End -->
    </div>
    <FooterVue></FooterVue>
  </div>
</template>

<script lang="ts">
import Vue from 'vue'
import { Component } from 'vue-property-decorator'
import { State } from 'vuex-class'
import FooterVue from './Footer.vue'
import * as apiDownload from '@/api/download'
import * as lodash from 'lodash'

@Component({
  components: {
    FooterVue
  }
})
export default class Home extends Vue {
  @State('debug')
  stateDebug: undefined;

  @State('weteoes')
  stateWeteoes: any;

  navNowSelect = ''; // 当前Nav选择
  downloadUrlList: Map<string, string> = new Map(); // 下载URL

  navSelectHandle (key: string, keyPath: Array<string>) {
    if (key === null) return
    switch (key) {
      case 'GitHub': {
        (this.$refs.GitHub as HTMLAnchorElement).click()
        break
      }
    }
    if (this.stateDebug) { this.log('navHandle', key, keyPath) }
  }

  // 初始化下载地址
  downloadReady () {
    apiDownload.downloadList()
      .then((e: any) => {
        const data = e.data
        for (const only of data) {
          const onlyKey: string = only.key
          const onlyURL: string = only.url
          this.downloadUrlList.set(onlyKey, onlyURL)
        }
      })
      .catch((e: object) => {
        this.log('获取下载地址失败')
        console.error(e)
      })
  }

  // 下载事件
  downloadBuuton = lodash.throttle((key: string) => {
    if (key === null) return
    const url = this.downloadUrlList.get(key)
    if (url === undefined) return
    apiDownload.downloadLog({ type: key })
      .catch((e: object) => { console.error(e) })
    window.open(url)
    if (this.stateDebug) { this.log('download', key, url) }
  }, 1000, {
    trailing: false
  })

  log (...data: any) {
    console.log(...data)
  }

  mounted () {
    this.downloadReady()
  }
}
</script>

<style lang="scss" scoped>
$bodyWidth: 1200px;

@mixin user-select($arg) {
  user-select: $arg;
  -moz-user-select: $arg;
  -webkit-user-select: $arg;
  -ms-user-select: $arg;
}

#Home {
  min-width: $bodyWidth;
  @include user-select(none);
}

nav {
  $navHeight: 61px; // element-ui（don't modify）
  .logo {
    cursor: default;
    img {
      height: $navHeight - 25px
    }
    span {
      padding-left: 10px;
      color: #000
    }
  }
  a {
    text-decoration: none;
    display: none;
  }
}
.step {
  > .onlyStep {
    display: flex;
    width: $bodyWidth;
    margin: 50px auto 100px auto;
    padding: 20px 0;

    > .png {
      flex: 2;
      text-align: center;
    }
    > .data {
      flex: 1;
    }
  }
}

.onlyStepData {
  display: flex;
  flex-direction: column;
  justify-content: center;

  > .data {
    width: 300px;
    height: auto;
    margin: 20px auto;
    %textMargin {
      margin: 10px auto;
    }
    > .title {
      font-size: 26px;
      text-align: center;
      @extend %textMargin;
    }
    > .text {
      font-size: 15px;
      @extend %textMargin;
    }
  }
}

.downloadData {
  width: 100%;
  min-height: 100px;
  padding-top: 60px;
  > .title {
    font-size: 24px;
  }
  > .downloadBuuton {
    margin-top: 20px;
  }
}
</style>
