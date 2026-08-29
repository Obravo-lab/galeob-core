/* Copyright (c) 2025 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import Icon from '@brave/leo/react/icon'

import { SearchBox } from './search/search_box'
import { Background } from './background/background'
import { BackgroundClickRegion } from './background/background_click_region'
import { BackgroundCaption } from './background/background_caption'
import { SettingsModal, SettingsView } from './settings/settings_modal'
import { TopSites } from './top_sites/top_sites'
import { Clock } from './common/clock'
import { LazyNewsFeed } from './news/lazy_news_feed'
import { WidgetStack } from './widgets/widget_stack'
import { useSearchLayoutReady, useWidgetLayoutReady } from './app_layout_ready'
import useMediaQuery from '$web-common/useMediaQuery'

import { style, threeColumnBreakpoint } from './app.style'

// <if expr="enable_ai_chat">
import { useNewTabState } from '../context/new_tab_context'
import { LazyQueryBox } from './query_box/lazy_query_box'
// </if>

const threeColumnQuery = `(width > ${threeColumnBreakpoint})`

export function App() {
  const searchLayoutReady = useSearchLayoutReady()
  const widgetLayoutReady = useWidgetLayoutReady()

  const [settingsView, setSettingsView] = React.useState<SettingsView | null>(
    null,
  )

  const threeColumnWidth = useMediaQuery(threeColumnQuery)

  React.useEffect(() => {
    const params = new URLSearchParams(location.search)
    const settingsArg = params.get('openSettings')
    if (settingsArg === null) {
      return
    }
    setSettingsView(settingsArg === 'BraveNews' ? 'news' : 'background')
    history.pushState(null, '', '/')
  }, [])

  return (
    <div data-css-scope={style.scope}>
      <Background />
      <div className='background-filter allow-background-pointer-events' />
      <main className='allow-background-pointer-events'>
        <button
          className='clock'
          onClick={() => setSettingsView('clock')}
        >
          <Clock />
        </button>
        <button
          className='settings'
          onClick={() => setSettingsView('background')}
        >
          <Icon name='settings' />
        </button>
        <div className='topsites-container allow-background-pointer-events'>
          <TopSites />
        </div>
        <div className='searchbox-container allow-background-pointer-events'>
          {searchLayoutReady && (
            <Search showSearchSettings={() => setSettingsView('search')} />
          )}
        </div>
        <div
          className='
          spacer
          sponsored-background-safe-area
          allow-background-pointer-events'
        >
          <BackgroundClickRegion />
        </div>
        <div className='caption-container allow-background-pointer-events'>
          <BackgroundCaption />
        </div>
        <div className='widget-container allow-background-pointer-events'>
          {widgetLayoutReady && (
            <>
              {threeColumnWidth ? (
                <>
                  <WidgetStack
                    name='left'
                    tabs={[]}
                  />
                  <WidgetStack
                    name='center'
                    tabs={['news']}
                  />
                </>
              ) : (
                <WidgetStack
                  name='left'
                  tabs={['news']}
                />
              )}
              <WidgetStack
                name='right'
                tabs={['vpn', 'rewards', 'talk']}
              />
            </>
          )}
        </div>
      </main>
      <div className='news-container'>
        <LazyNewsFeed />
      </div>
      <img
        className='brand-logo'
        alt=''
        src='data:image/png;base64,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'
      />
      <SettingsModal
        isOpen={settingsView !== null}
        initialView={settingsView}
        onClose={() => setSettingsView(null)}
      />
    </div>
  )
}

function Search(props: { showSearchSettings: () => void }) {
  // <if expr="enable_ai_chat">
  const aiChatInputEnabled = useNewTabState((s) => s.aiChatInputEnabled)
  if (aiChatInputEnabled) {
    return <LazyQueryBox showSearchSettings={props.showSearchSettings} />
  }
  // </if>
  return <SearchBox showSearchSettings={props.showSearchSettings} />
}
