<template>
  <div id="Index">
    <div class="top">
      <div class="one">
        <div class="logo">
          <img src="/static/logo.png" />
          <div>密码保管箱 - Password Box</div>
        </div>
        <div class="operating">
          <a target="_blank" href="https://github.com/Weteoes/PasswordBox">
            <a-button @click="downloadLog('github')">GitHub</a-button>
          </a>
        </div>
      </div>
      <div class="data">
        <div class="left">
          <img src="/static/software.jpg" />
        </div>
        <div class="right">
          <div class="title">密码保管箱</div>
          <div class="info">不再忘记密码，强密码解决方案</div>
          <div class="info">
            使用AES 256加密算法，可自动登录网页，数据云同步，多浏览器支持
          </div>
          <div class="download">
            <div class="title">下载地址：</div>
            <a-button class="only" @click="downloadBuuton('browser')">
              浏览器插件
            </a-button>
            <a-button class="only" @click="downloadBuuton('win')">
              电脑客户端
            </a-button>
          </div>
        </div>
      </div>
    </div>
    <div class="features">
      <div class="title">加密算法不可逆</div>
      <div class="info">若加密密钥丢失，数据将无法被再次解密</div>
      <div class="more">
        <!-- 安全 -->
        <div class="only">
          <div class="icon">
            <a-icon type="safety" />
          </div>
          <div class="title">安全</div>
          <div class="info">
            AES 256 加密算法，在遗失密码的情况下数据将无法被再次解密
          </div>
        </div>
        <!-- 云同步 -->
        <div class="only">
          <div class="icon">
            <a-icon type="cloud" />
          </div>
          <div class="title">云同步</div>
          <div class="info">
            支持SSO单点登录，将加密后的数据保存云端，在无密码的情况下，该数据无法被解读
          </div>
        </div>
        <!-- 本地工作模式 -->
        <div class="only">
          <div class="icon">
            <a-icon type="desktop" />
          </div>
          <div class="title">本地工作模式</div>
          <div class="info">
            支持本地工作模式，数据将保存在本地，可在无需网络的环境下使用
          </div>
        </div>
      </div>
    </div>
    <FooterVue></FooterVue>
  </div>
</template>

<script lang="ts">
import Vue from 'vue'
import { Component } from 'vue-property-decorator'
import FooterVue from '@/layouts/Footer.vue'
import * as apiDownload from '@/api/download'
import * as lodash from 'lodash'

@Component({
  components: {
    FooterVue,
  },
  head() {
    return {
      title: '主页',
    }
  },
})
export default class Index extends Vue {
  // 下载URL
  downloadUrlList: Map<string, string> = new Map()

  // 初始化下载地址
  downloadReady() {
    apiDownload
      .downloadList()
      .then((e: any) => {
        const data = e.data
        for (const only of data) {
          const onlyKey: string = only.key
          const onlyURL: string = only.url
          this.downloadUrlList.set(onlyKey, onlyURL)
        }
      })
      .catch((e: object) => {
        console.error(e)
      })
  }

  // 下载事件
  downloadBuuton = lodash.throttle(
    (key: string) => {
      if (key === null) return
      this.downloadLog(key)
      const url = this.downloadUrlList.get(key)
      if (url === undefined) return
      window.open(url)
    },
    1000,
    {
      trailing: false,
    }
  )

  // 日志
  downloadLog(key: String) {
    apiDownload.downloadLog({ type: key }).catch((e: object) => {
      console.error(e)
    })
  }

  mounted() {
    this.downloadReady()
    this.downloadLog('website')
  }
}
</script>

<style lang="less" scoped>
#Index {
  @minWidth: 1200px;

  & {
    min-width: @minWidth;
  }

  > .top {
    @padding: 30px;

    & {
      width: 100%;
      height: 600px;
      background: linear-gradient(30deg, #1f95ff 0, #42d0f7);
    }

    > .one {
      & {
        .minWidth();
        padding-top: 10px;
        height: 55px;
      }
      > .logo {
        & {
          height: 100%;
          padding-left: @padding;
          float: left;
        }
        > img {
          width: 40px;
        }
        > div {
          color: #fff;
          font-size: 18px;
          line-height: 40px;
          padding-left: 10px;
          float: right;
        }
      }
      > .operating {
        height: 100%;
        float: right;
        padding-top: 5px;
        padding-right: @padding;
      }
    }

    > .data {
      & {
        .minWidth();
        padding: 80px @padding 0;
      }
      > .left {
        @width: 600px;
        & {
          width: @width;
        }
        > img {
          width: @width;
          float: left;
        }
      }
      > .right {
        & {
          width: 340px;
          padding-right: 30px;
          color: #fff;
          float: right;
          font-size: 16px;
        }

        > .title {
          font-weight: bold;
          font-size: 30px;
          padding: 30px;
          padding-left: 0;
        }

        > .info {
          padding: 3px;
          padding-left: 0;
        }

        > .download {
          & {
            padding-top: 40px;
          }
          > .title {
            padding-bottom: 10px;
          }
          > .only {
            margin: 5px;
            margin-left: 0;
          }
        }
      }
    }
  }

  > .features {
    & {
      .minWidth();
      padding: 30px 0;
    }

    > .title {
      font-weight: bold;
      font-size: 32px;
      text-align: center;
    }

    > .info {
      padding-top: 5px;
      color: #808080;
      text-align: center;
    }

    > .more {
      & {
        display: flex;
        justify-content: space-between;
      }

      > .only {
        & {
          width: 250px;
          text-align: center;
          padding: 10px;
        }
        > .icon {
          font-size: 46px;
        }
        > .title {
          font-size: 16px;
          padding-bottom: 10px;
        }
      }
    }
  }

  .minWidth() {
    width: @minWidth;
    margin: 0 auto;
  }
}
</style>

<style lang="less">
#Index {
  button.ant-btn {
    & {
      background: transparent;
      color: #fff;
      border: 1px solid #fff;
      transition: 0.5s;
    }
    &:hover {
      background: #fff;
      color: #000;
    }
  }
}
</style>
