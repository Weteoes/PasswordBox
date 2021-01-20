import Vue from 'vue'
declare module '*.vue' {
  export default Vue
}

export declare interface Common {
  getQueryVariable(content: String): String
}

declare module 'vue/types/vue' {
  interface Vue {
    $common: Common // 公共脚本
    _title: string | undefined // 用于页面标题
  }
}
