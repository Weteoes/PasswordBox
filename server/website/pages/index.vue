<template>
  <div id="Index">
    <div class="top">
      <a-affix class="affix">
        <div class="one">
          <div class="center">
            <div class="logo">
              <img src="/static/logo.png" />
              <div>密码保管箱</div>
            </div>
            <div class="operating">
              <div v-if="logged">
                <a-popover placement="bottom">
                  <template slot="content">
                    <div class="userOperatingPopover">
                      <div id="signOut" class="only" @click="ssoSignOut">
                        退出登录
                      </div>
                    </div>
                  </template>
                  <div>
                    <a-avatar
                      shape="square"
                      :style="{
                        backgroundColor: 'rgb(80 166 204)',
                        verticalAlign: 'middle',
                      }"
                      v-text="userInfo.user"
                    ></a-avatar>
                  </div>
                </a-popover>
              </div>
              <div v-else>
                <a-button class="only" @click="ssoRegistered">
                  注册账户
                </a-button>
                <a-button class="only" @click="ssoLogin"> 登录 </a-button>
              </div>
            </div>
          </div>
        </div>
      </a-affix>
      <div class="data">
        <div class="left">
          <img src="/static/software.jpg" />
        </div>
        <div class="right">
          <div class="title">密码保管箱</div>
          <div class="info">从此不再忘记密码，强密码解决方案</div>
          <div class="info">
            使用AES 256加密算法，可自动登录网页，数据云同步，支持主流浏览器
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
          <div class="github">
            <div class="title">GitHub：</div>
            <a target="_blank" href="https://github.com/Weteoes/PasswordBox">
              <a-button @click="downloadLog('github')">GitHub</a-button>
            </a>
          </div>
        </div>
      </div>
    </div>
    <div class="features featuresNoneBorder">
      <div class="onlyFeatures">
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
    </div>
    <div class="features">
      <div class="onlyFeatures onlyFeaturesTwo">
        <div class="title">免费使用</div>
        <div class="info">无需任何额外收费</div>
        <div class="more">
          <!-- 安全 -->
          <div class="only">
            <div class="icon">
              <a-icon type="key" />
            </div>
            <div class="title">无限</div>
            <div class="info">不限数量的网站账户信息记录</div>
          </div>
          <!-- 云同步 -->
          <div class="only">
            <div class="icon">
              <a-icon type="chrome" />
            </div>
            <div class="title">支持主流浏览器</div>
            <div class="info">支持基于Chrome制作的所有主流浏览器</div>
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
import { Getter, Action, namespace } from 'vuex-class'
import FooterVue from '@/layouts/Footer.vue'
import * as apiDownload from '@/api/download'
import * as apiSSO from '@/api/sso'
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
  // 是否已经登录
  logged: boolean = false
  // 登录信息
  userInfo: object = {
    id: null,
    uid: 'B23028DA-E444-4C1F-BB5E-E6AB09746372',
    user: 'a',
    code: 0,
  }

  // 下载URL
  downloadUrlList: Map<string, string> = new Map()
  // 注册账号URL
  ssoRegisteredUrl: string = 'https://sso.weteoes.cn/Registered/byMail/?'
  // 登录账号URL
  @namespace('sso').Getter('ssoLoginUrl') ssoLoginUrl: string |undefined
  @namespace('sso').Getter('ssoSignOutUrl') ssoSignOutUrl: string |undefined

  // 初始化下载地址
  downloadReady() {
    apiDownload
      .downloadList()
      .then((e: any) => {
        if (e.code === 0) {
          const data = e.data
          for (const only of data) {
            const onlyKey: string = only.key
            const onlyURL: string = only.url
            this.downloadUrlList.set(onlyKey, onlyURL)
          }
        } else {
          this.showErrorInfo('获取下载地址错误')
        }
      })
      .catch((e: object) => {
        window.console.error(e)
      })
  }

  // 下载事件throttle
  downloadBuuton = lodash.throttle(this.downloadBuuton_, 1000, {
    trailing: false,
  })

  // 注册账号事件throttle
  ssoRegistered = lodash.throttle(this.ssoRegistered_, 1000, {
    trailing: false,
  })

  // 登录账号事件throttle
  ssoLogin = lodash.throttle(this.ssoLogin_, 1000, {
    trailing: false,
  })

  // 注销账号事件throttle
  ssoSignOut = lodash.throttle(this.ssoSignOut_, 1000, {
    trailing: false,
  })

  // 下载事件
  downloadBuuton_(key: string) {
    if (key === null) return
    this.downloadLog(key)
    const url = this.downloadUrlList.get(key)
    if (url === undefined) return
    window.open(url)
  }

  // 注册账号事件
  ssoRegistered_() {
    const url =
      this.ssoRegisteredUrl + 'callback=' + encodeURIComponent(location.href)
    if (url === undefined) return
    window.open(url)
  }

  // 登录账号事件
  ssoLogin_() {
    const url = this.ssoLoginUrl + encodeURIComponent(location.href)
    if (url === undefined) return
    location.href = url
  }

  // 注销账号
  ssoSignOut_() {
    const url = this.ssoSignOutUrl + encodeURIComponent(location.href)
    if (url === undefined) return
    location.href = url
  }

  // 尝试获取登录信息
  getLoggedInfo() {
    apiSSO
      .getInfo()
      .then((e: any) => {
        if (e.code === 0) {
          this.logged = true
          this.userInfo = e
        } else {
          this.logged = false
        }
      })
      .catch((e: object) => {
        console.error(e)
      })
  }

  // 访问日志
  downloadLog(key: String) {
    if (location.hostname === '127.0.0.1') return
    if (this.$common.getQueryVariable('w') === '1') return
    apiDownload.downloadLog({ type: key }).catch((e: object) => {
      window.console.error(e)
    })
  }

  /**
   * Default
   */
  // 全局错误提示
  showErrorInfo(msg: string | undefined) {
    if (msg) {
      this.$message.destroy()
      this.$message.error(msg)
    }
  }

  mounted() {
    this.downloadReady()
    this.getLoggedInfo()
    this.downloadLog('website')
    ;(<any>window).a = this
  }
}
</script>

<style lang="less" scoped>
#Index {
  > .top {
    // 导航栏
    > .affix .one {
      > .center {
        > .operating {
        }
      }
    }
  }
  @media screen and (min-width: 601px) {
    @minWidth: 1200px;
    & {
      min-width: @minWidth;
    }

    > .top {
      @padding: 30px;

      & {
        width: 100%;
        padding-bottom: 60px;
        background: linear-gradient(30deg, #1f95ff 0, #42d0f7);
      }

      // 导航条固定在头部时
      .ant-affix .one {
        background: linear-gradient(30deg, #1f95ff 0, #42d0f7);
      }
      > .affix .one {
        & {
          padding-top: 10px;
          height: 60px;
        }
        > .center {
          & {
            .minWidth();
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
            padding: 4px 0;
            padding-right: @padding;
          }
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
            display: inline-block;
          }
          > img {
            width: @width;
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

          > .github {
            & {
              padding-top: 20px;
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

    > .featuresNoneBorder {
      border-top: none !important;
    }
    > .features {
      & {
        .minWidth();
        padding: 30px 0;
        border-top: 1px solid #e8e8e8;
      }

      > .onlyFeatures {
        width: 100%;
        margin: 0 auto;
      }

      > .onlyFeaturesTwo {
        width: 700px;
        margin: 0 auto;
      }

      .title {
        font-weight: bold;
        font-size: 32px;
        text-align: center;
      }

      .info {
        padding-top: 5px;
        color: #808080;
        text-align: center;
      }

      .more {
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

  @media screen and (max-width: 600px) {
    > .top {
      @padding: 5px;

      & {
        width: 100%;
        padding-bottom: 40px;
        background: linear-gradient(30deg, #1f95ff 0, #42d0f7);
      }

      // 导航条固定在头部时
      .ant-affix .one {
        background: linear-gradient(30deg, #1f95ff 0, #42d0f7);
      }
      > .affix .one {
        & {
          padding: 10px 0;
        }
        > .center {
          > .logo {
            & {
              .inline();
              height: 100%;
              padding-left: @padding;
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
            .inline();
            height: 100%;
            float: right;
            padding: 4px 0;
            padding-right: @padding;
          }
        }
      }

      > .data {
        & {
          padding: 25px @padding 0;
        }
        > .left {
          & {
            width: 100%;
            text-align: center;
          }
          > img {
            width: 90vw;
          }
        }
        > .right {
          & {
            width: 340px;
            padding-right: 30px;
            padding-left: 6px;
            color: #fff;
            font-size: 16px;
            margin: 0 auto;
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

          > .github {
            & {
              padding-top: 20px;
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

    > .featuresNoneBorder {
      border-top: none !important;
    }
    > .features {
      & {
        width: 95vw;
        margin: 0 auto;
        padding: 30px 0;
        border-top: 1px solid #e8e8e8;
      }

      > .onlyFeatures {
        width: 100%;
        margin: 0 auto;
      }

      .title {
        font-weight: bold;
        font-size: 32px;
        text-align: center;
      }

      .info {
        padding-top: 5px;
        color: #808080;
        text-align: center;
      }

      .more {
        & {
          display: flex;
          justify-content: space-between;
          flex-flow: column;
        }

        > .only {
          & {
            width: 250px;
            text-align: center;
            padding: 10px;
            margin: 0 auto;
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

    .inline() {
      display: inline-block;
      vertical-align: top;
    }
  }
}
</style>

<style lang="less">
#Index {
  // 按钮样式
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
  // 动画
  @keyframes animation_nav {
    0% {
      top: -60px;
    }

    to {
      top: 0;
    }
  }
  .affix > .ant-affix {
    animation: animation_nav 0.3s;
  }
}

// 因为dom有scoped，且不在#Index内
// 用户操作气泡
.userOperatingPopover {
  .only {
    & {
      width: 80px;
      height: 35px;
      line-height: 35px;
      transition: 0.2s;
      padding: 0 10px;
      border-radius: 3px;
    }
    &:hover {
      background: #dbdbdb;
    }
  }
  > #signOut {
    text-align: center;
    cursor: pointer;
  }
}
</style>
