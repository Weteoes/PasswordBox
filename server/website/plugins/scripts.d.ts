export declare interface Common {
  getQueryVariable(content: String): String
}

declare module 'vue/types/vue' {
  interface Vue {
    $common: Common
  }
}
