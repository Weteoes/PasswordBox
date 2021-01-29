<template>
  <div>404 Not Found</div>
</template>

<script lang="ts">
import Vue from 'vue'
import { Component } from 'vue-property-decorator'
import { namespace } from 'vuex-class'

@Component({
  props: ['error'],
  layout: 'error',
  head() {
    return {
      title: '页面未找到' + this._title,
    }
  },
})
export default class error404 extends Vue {
  @(namespace('seo').Getter('title')) _title: string | undefined
  mounted() {
    location.href = '/'
  }
}
</script>
